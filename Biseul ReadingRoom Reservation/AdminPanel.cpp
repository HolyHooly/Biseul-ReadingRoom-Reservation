#include "AdminPanel.h"
#include "ui_AdminPanel.h"


AdminPanel::AdminPanel(QWidget *parent) : QDialog(parent)
{
    ui->setupUi(this);

    int seat[] = {0,
                  0,0,0,1,1,1,1,1,1,1,1,0,
                  0,0,0,1,1,1,1,1,1,1,1,0,
                  0,1,1,1,1,1,1,1,1,1,1,0,
                  0,1,1,1,1,1,1,1,1,1,1,0,
                  0,1,1,1,1,1,1,1,1,1,1,0,
                  0,1,1,1,1,1,1,1,1,1,1,0,
                  0,0,1,1,1,1,1,1,1,1,1,1,
                  0,0,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,};

    QPushButton *s_seat[125];
    QGridLayout *grid_seat = new QGridLayout;

    int id = 1;

    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 12; j++) {
            if (j == 6) {
                grid_seat->addItem(new QSpacerItem(20,40, QSizePolicy::Minimum, QSizePolicy::Minimum), i, j);
            }
            if (seat[12*i + j+1] == 1) {
                s_seat[id] = new QPushButton(QString::number(id));
                connect(s_seat[id], SIGNAL(clicked()), this, SLOT(button_seat()));
                s_seat[id]->setObjectName("seat"+ QString::number(id));
                s_seat[id]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                if (j >= 6) {
                    grid_seat->addWidget(s_seat[id], i, j+1);
                }
                else {
                    grid_seat->addWidget(s_seat[id], i, j);
                }
                id += 1;
            }
        }
    }

    QVBoxLayout *side = new QVBoxLayout;
    QPushButton *stu_list = new QPushButton("Student List");
    QCheckBox *box1 = new QCheckBox("Return");
    QCheckBox *box2 = new QCheckBox("Caution");
    QCheckBox *box3 = new QCheckBox("Pause Set/Unset");
    QPushButton *ac = new QPushButton("Setting Done");

    QPushButton *recent = new QPushButton("Restore Recent Info");
    QPushButton *save = new QPushButton("Save Current Info");
    QPushButton *exit = new QPushButton("Exit Program");

    side->addWidget(stu_list);
    side->addSpacing(5);
    side->addWidget(box1);
    side->addWidget(box2);
    side->addWidget(box3);
    side->addSpacing(5);
    side->addWidget(ac);
    side->addSpacing(30);
    side->addWidget(recent);
    side->addSpacing(10);
    side->addWidget(save);
    side->addSpacing(10);
    side->addWidget(exit);

    auto sty_exit = "background-color : red; border: 2px solid black;";
    auto sty_above = "background-color : #64ffec; border: 2px solid black;";
    auto sty_recent = "background-color : #ffb28a; border: 2px solid black;";
    auto sty_save = "background-color : #fdff93; border: 2px solid black;";
    exit->setStyleSheet({sty_exit});
    stu_list->setStyleSheet({sty_above});
    ac->setStyleSheet({sty_above});
    recent->setStyleSheet({sty_recent});
    save->setStyleSheet({sty_save});


    QGridLayout *top = new QGridLayout;
    top->addLayout(grid_seat,0,0,4,4);
    top->addLayout(side, 0, 4, 1, 4);



    // info of student
    QTableView *table = new QTableView;
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //side2
    QVBoxLayout *side2 = new QVBoxLayout;

    QLabel *sea = new QLabel("Searching");
    sea->setStyleSheet({"font: 12pt;"});
    sea->setAlignment(Qt::AlignLeft);
    QLabel *sta = new QLabel("Name, Hackbun, RFID");
    sta->setStyleSheet({"font: 15pt;"});
    sta->setAlignment(Qt::AlignCenter);
    QLineEdit *sea2 = new QLineEdit();
    sea2->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sea2->setMinimumWidth(200);
    QPushButton *b1 = new QPushButton("Warning");
    QPushButton *b2 = new QPushButton("Ban");
    QPushButton *b3 = new QPushButton("Delete Warning");
    QPushButton *b4 = new QPushButton("Remove");

    auto sty_warn = "font: 12pt; border : 2pt solid black; background-color:#b0c5ff; qproperty-icon: url(/Users/admin/Desktop/temp/so/warning.png); qproperty-iconSize: 25px 25px;";
    auto sty_ban = "font: 12pt; border : 2pt solid black; background-color:#e4ff7a; qproperty-icon: url(/Users/admin/Desktop/temp/so/ban.png); qproperty-iconSize: 25px 25px;";
    auto sty_delwarn = "font: 12pt; border : 2pt solid black; background-color:#ff9c42; qproperty-icon: url(/Users/admin/Desktop/temp/so/on.png); qproperty-iconSize: 25px 25px;";
    auto sty_remove = "font: 12pt; border : 2pt solid black; background-color:#ff122c; qproperty-icon: url(/Users/admin/Desktop/temp/so/remove.png); qproperty-iconSize: 25px 25px;";

    b1->setStyleSheet(sty_warn);
    b2->setStyleSheet(sty_ban);
    b3->setStyleSheet(sty_delwarn);
    b4->setStyleSheet(sty_remove);

    side2->addWidget(sea);
    side2->addSpacing(20);
    side2->addWidget(sta);
    side2->addSpacing(15);
    side2->addWidget(sea2);
    side2->addSpacing(10);
    side2->addWidget(b1);
    side2->addSpacing(5);
    side2->addWidget(b2);
    side2->addSpacing(5);
    side2->addWidget(b3);
    side2->addSpacing(5);
    side2->addWidget(b4);


    QGridLayout *bot = new QGridLayout;
    bot->addWidget(table, 0, 0, 4, 4);
    bot->addLayout(side2, 0, 4);

    // Whole layout
    QGridLayout *whole = new QGridLayout;
    whole->addLayout(top, 0, 0);
    whole->addLayout(bot, 1, 0);

    setLayout(whole);
    setModal(true);
    setWindowTitle("Administer Page");
    setFixedSize(1025,1000);

}

AdminPanel::~AdminPanel()
{
}
