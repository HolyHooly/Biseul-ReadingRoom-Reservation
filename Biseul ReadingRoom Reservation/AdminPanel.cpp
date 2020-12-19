///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 12. 20. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////
#include "AdminPanel.h"
#include "ui_AdminPanel.h"



AdminPanel::AdminPanel(QWidget *parent, biseul_rroom::SeatManager& exe_manager) : QDialog(parent)
{
    //window setting
    exe_manager_ptr = &exe_manager;
    ui->setupUi(this);
    setModal(true);
    setWindowTitle("Administrator");
    setFixedSize(1010, 510);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //no hint button

    //whole layout setting
    QHBoxLayout* seat_page_whole_layout = new QHBoxLayout();
    //Tab main menu setting
    QTabWidget* main_menu = new QTabWidget(this); //main menu as tab widget
    main_menu->setGeometry(5, 5, 1000, 500);

    QString seat_panel_str = QString::fromLocal8Bit("자리 관리");
    QString stud_panel_str = QString::fromLocal8Bit("학생 관리");
    QWidget* seat_panel = new QWidget(); //QWidget for the first panel
    main_menu->addTab(seat_panel, seat_panel_str);
    QWidget* stud_panel = new QWidget(); //Qwidget second panel
    main_menu->addTab(stud_panel, stud_panel_str);
    
    //==========================seat panel setting========================
    //seat button setting
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
                  1,1,1,1,1,1,1,1,1,1,1,1,}; //reading room seat information
    QGridLayout *grid_seat = new QGridLayout; //seat button grid for GUI

    int id = 1; //seat number temp variable
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 12; j++) {
            if (j == 6) {
                grid_seat->addItem(new QSpacerItem(20,40, QSizePolicy::Minimum, QSizePolicy::Minimum), i, j);
            }
            if (seat[12*i + j+1] == 1) {
                s_seat[id] = new QPushButton(QString::number(id));
                s_seat[id]->setObjectName(QString::number(id));
                s_seat[id]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                s_seat[id]->setCheckable(true);
                s_seat[id]->setChecked(false);

                if (exe_manager.get_seat(id) == nullptr) s_seat[id]->setStyleSheet(vacant_unchecked_style);
                else if (exe_manager.get_seat(id)->get_status() == biseul_rroom::SeatStatus::Occupied) s_seat[id]->setStyleSheet(reserved_unchecked_style);
                else if (exe_manager.get_seat(id)->get_status() == biseul_rroom::SeatStatus::Paused) s_seat[id]->setStyleSheet(paused_unchecked_style);
                
                connect(s_seat[id], SIGNAL(clicked()), this, SLOT(seat_button_clicked()));
         
                if (j >= 6) {
                    grid_seat->addWidget(s_seat[id], i, j+1);
                }
                else {
                    grid_seat->addWidget(s_seat[id], i, j);
                }
                id += 1;
            }
        }
    } //seat button grid done

    //side menu setting
    QVBoxLayout *side_menu_layout = new QVBoxLayout;
    QPushButton *ac = new QPushButton(QString::fromLocal8Bit("처리"));
    connect(ac, SIGNAL(clicked()), this, SLOT(execute_button_clicked()));

    box_group.addButton(pause_box);

    connect(return_box, SIGNAL(clicked()), this, SLOT(return_box_clicked()));
    connect(warning_box, SIGNAL(clicked()), this, SLOT(return_box_clicked()));
    connect(pause_box, SIGNAL(clicked()), this, SLOT(pause_box_clicked()));


    QPushButton *recent = new QPushButton(QString::fromLocal8Bit("최근 자리 정보 불러오기"));
    QPushButton *save = new QPushButton(QString::fromLocal8Bit("최근 자리 정보 저장"));
    QPushButton *exit = new QPushButton(QString::fromLocal8Bit("프로그램 종료"));
    connect(recent, SIGNAL(clicked()), this, SLOT(recent_button_clicked()));
    connect(save, SIGNAL(clicked()), this, SLOT(save_button_clicked()));
    connect(exit, SIGNAL(clicked()), this, SLOT(exit_button_clicked()));

    side_menu_layout->addWidget(return_box);
    side_menu_layout->addWidget(warning_box);
    side_menu_layout->addWidget(pause_box);
    side_menu_layout->addSpacing(5);
    side_menu_layout->addWidget(ac); //처리버튼
    side_menu_layout->addSpacing(50);
    side_menu_layout->addWidget(recent);
    side_menu_layout->addSpacing(10);
    side_menu_layout->addWidget(save);
    side_menu_layout->addSpacing(10);
    side_menu_layout->addWidget(exit);

    auto sty_exit = "background-color : red; border: 2px solid black; padding: 3px;";
    auto sty_above = "background-color : #64ffec; border: 2px solid black;padding: 3px;";
    auto sty_recent = "background-color : #ffb28a; border: 2px solid black;padding: 3px;";
    auto sty_save = "background-color : #fdff93; border: 2px solid black;padding: 3px;";
    exit->setStyleSheet({sty_exit});
    ac->setStyleSheet({sty_above});
    recent->setStyleSheet({sty_recent});
    save->setStyleSheet({sty_save});

    seat_page_whole_layout->addLayout(grid_seat);
    seat_page_whole_layout->addLayout(side_menu_layout);
    seat_panel->setLayout(seat_page_whole_layout);


    //=======================Stuendt Tab=============================
    QHBoxLayout* stud_page_whole_layout = new QHBoxLayout();

    // info of student
    QTableView *table = new QTableView;
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //filter_model->setSourceModel() 할것: table에 데이터 가져오는거
    //keyword: 안녕하이
    filter_model->setFilterKeyColumn(-1);

    table->setModel(filter_model);


    //layout
    //side2
    QVBoxLayout *side2 = new QVBoxLayout;

    QLabel *sea = new QLabel("Search");
    sea->setStyleSheet({"font: 12pt;"});
    sea->setAlignment(Qt::AlignLeft);
    QLabel *sta = new QLabel("Name, Student ID, or RFID");
    sta->setStyleSheet({"font: 12pt;"});
    sta->setAlignment(Qt::AlignCenter);
    QLineEdit *sea2 = new QLineEdit();
    sea2->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sea2->setMinimumWidth(200);
    QPushButton *b1 = new QPushButton(QString::fromLocal8Bit("경고 추가"));
    QPushButton *b2 = new QPushButton(QString::fromLocal8Bit("제명"));
    QPushButton *b3 = new QPushButton(QString::fromLocal8Bit("경고 초기화"));
    QPushButton *b4 = new QPushButton(QString::fromLocal8Bit("삭제"));

    auto sty_warn = "font: 12pt; border : 2pt solid black; background-color:#b0c5ff; qproperty-icon: url(./assets/warning.png); qproperty-iconSize: 25px 25px;";
    auto sty_ban = "font: 12pt; border : 2pt solid black; background-color:#e4ff7a; qproperty-icon: url(./assets/ban.png); qproperty-iconSize: 25px 25px;";
    auto sty_delwarn = "font: 12pt; border : 2pt solid black; background-color:#ff9c42; qproperty-icon: url(./assets/on.png); qproperty-iconSize: 25px 25px;";
    auto sty_remove = "font: 12pt; border : 2pt solid black; background-color:#ff122c; qproperty-icon: url(./assets/remove.png); qproperty-iconSize: 25px 25px;";

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

    stud_page_whole_layout->addWidget(table);
    stud_page_whole_layout->addLayout(side2);
    stud_panel->setLayout(stud_page_whole_layout);

}

AdminPanel::~AdminPanel()
{
    delete return_box;
    delete warning_box;
    delete pause_box;
    
    delete filter_model;


}

void AdminPanel::return_box_clicked()
{
    box_group.setExclusive(false);
    pause_box->setChecked(false);
    box_group.setExclusive(true);

}

void AdminPanel::pause_box_clicked()
{
    return_box->setChecked(false);
    warning_box->setChecked(false);
    pause_box->setChecked(true);
    
}

void AdminPanel::execute_button_clicked()
{


    for (int i = 0; i < READINGROOM_SEAT; ++i) {
        
    
    
    }

}

void AdminPanel::recent_button_clicked()
{
    biseul_rroom::Loading loader;
    loader.load_status();
    exe_manager_ptr->load_seat_vector(loader.get_seats_info_vector());

    //할것: 로그 추가

}

void AdminPanel::save_button_clicked()
{
    biseul_rroom::save_status(exe_manager_ptr->get_reserved_seat_vector());

    //할것: 로그 추가
}

void AdminPanel::exit_button_clicked()
{
}

void AdminPanel::seat_button_clicked() {
    QObject* obj = sender();
    int num = obj->objectName().toInt();

    if (!s_seat[num]->isChecked()) {
        if (exe_manager_ptr->get_seat(num) == nullptr) s_seat[num]->setStyleSheet(vacant_unchecked_style); //to vacant unchecked style
        else if (exe_manager_ptr->get_seat(num)->get_status() == biseul_rroom::SeatStatus::Occupied) s_seat[num]->setStyleSheet(reserved_unchecked_style); //to occupied unchecked style
        else if (exe_manager_ptr->get_seat(num)->get_status() == biseul_rroom::SeatStatus::Paused) s_seat[num]->setStyleSheet(paused_unchecked_style);
        s_seat[num]->setChecked(false);
    }
    else {
        if (exe_manager_ptr->get_seat(num) == nullptr) s_seat[num]->setStyleSheet(vacant_checked_style); //to vacant unchecked style
        else if (exe_manager_ptr->get_seat(num)->get_status() == biseul_rroom::SeatStatus::Occupied) s_seat[num]->setStyleSheet(reserved_checked_style); //to occupied unchecked style
        else if (exe_manager_ptr->get_seat(num)->get_status() == biseul_rroom::SeatStatus::Paused) s_seat[num]->setStyleSheet(paused_checked_style);
        s_seat[num]->setChecked(true);
    }


}