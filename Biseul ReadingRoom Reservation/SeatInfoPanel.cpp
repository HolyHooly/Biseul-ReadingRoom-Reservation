#include "SeatInfoPanel.h"
#include "ui_SeatInfoPanel.h"

SeatInfoPanel::SeatInfoPanel(QWidget *parent, const int seat_num, const std::string name, const tm* reserved_time, const tm* reserve_end_time, const int pause_left_time) :
    QDialog(parent),
    ui(new Ui::SeatInfoPanel)
{
    ui->setupUi(this);

    setWindowTitle("Seat Info");
    setWindowIcon(QIcon("./assets/icon.png"));
    setStyleSheet({ "background-color:rgb(255,255,255);" });
    setFixedSize(400, 400);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //취소버튼
    n_button = new QPushButton("Ok");
    n_button->setStyleSheet({ "background-color: white; border:3px solid black; padding: 5px;" });

    QString title_inside = "Seat Number: ";
    QString num_qstr = QString::number(seat_num);
    title_inside.append(num_qstr);
    position_label = new QLabel(title_inside);
    name_label = new QLabel("Name");
    time_label = new QLabel("Reserved Time");
    time_end_label = new QLabel("Time end");
    pause_label = new QLabel("Pause left Time");

    auto style = "font: 63 12pt Yu Gothic UI Semibold;";
    name_label->setStyleSheet({style});
    time_label->setStyleSheet({style});
    time_end_label->setStyleSheet({ style });
    pause_label->setStyleSheet({ style });
    name_label->setAlignment(Qt::AlignCenter);
    time_label->setAlignment(Qt::AlignCenter);
    time_end_label->setAlignment(Qt::AlignCenter);
    pause_label->setAlignment(Qt::AlignCenter);

    // get info here==========================================

    int len = name.length();
    std::string new_name;
    if (len >= 3) {
        for (int i = 0; i < (len - 1) / 2; ++i) {
            new_name.push_back(name[i]);
        }
        for (int i = (len-1)/2; i < len/2 +1; ++i) {
            new_name.push_back('*');
        }
        for (int i = len/2 +1; i < len; ++i) {
            new_name.push_back(name[i]);
        }
    }
    char temp_name[100];
    strcpy(temp_name, new_name.c_str());
    QString name_qstr = QString::fromLocal8Bit(temp_name);;
    QLabel *get_name = new QLabel(name_qstr);

    QString time_qstr = "";
    time_qstr.append(QString::number(reserved_time->tm_hour));
    time_qstr.append(":");
    time_qstr.append(QString::number(reserved_time->tm_min));
    QLabel *get_time = new QLabel(time_qstr);

    QString time_end_qstr = "";
    time_end_qstr.append(QString::number(reserve_end_time->tm_hour));
    time_end_qstr.append(":");
    time_end_qstr.append(QString::number(reserve_end_time->tm_min));
    QLabel* get_time_end = new QLabel(time_end_qstr);

    QString temp_pause = " min";
    QLabel* get_pause = new QLabel(QString::number(pause_left_time).append(temp_pause));
    //==========================================================

    get_name->setStyleSheet({"font: 63 12pt Yu Gothic UI Semibold;"});
    get_time->setStyleSheet({"font: 63 12pt Yu Gothic UI Semibold;"});
    get_time_end->setStyleSheet({ "font: 63 12pt Yu Gothic UI Semibold;" });
    get_pause->setStyleSheet({"font: 63 12pt Yu Gothic UI Semibold;"});

    QGridLayout *whole = new QGridLayout;
//    whole->addWidget(position_label,0,0);
    whole->addWidget(name_label, 1, 0);
    whole->addWidget(get_name, 1, 1);
    whole->addWidget(time_label, 2, 0);
    whole->addWidget(get_time, 2, 1);
    whole->addWidget(time_end_label, 3, 0);
    whole->addWidget(get_time_end, 3, 1);
    whole->addWidget(pause_label, 4, 0);
    whole->addWidget(get_pause, 4, 1);
    whole->addWidget(n_button, 5, 0, 1, 2);

    setLayout(whole);
    setModal(true);
    setFixedSize(400,300);

    // connect button
    connect(n_button, SIGNAL(clicked()), this, SLOT(cancel()));
}

SeatInfoPanel::~SeatInfoPanel()
{
    delete ui;
}

void SeatInfoPanel::cancel() {
    this->close();
}
