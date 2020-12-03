#include "BiseulReadingRoomReservation.h"
#include <iostream>

BiseulReadingRoomReservation::BiseulReadingRoomReservation(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this); //default setup

	whole = new QGridLayout;
	main = new QWidget;

	//title of the program
	//layout setting
	QHBoxLayout* title_layout = new QHBoxLayout;
	QLabel* title_label = new QLabel(QString::fromLocal8Bit("비슬빌리지 독서실 예약시스템"));
	auto sty_t = "font: 20pt Futura;";
	title_label->setStyleSheet({ sty_t });

	
	QPixmap icon_pix = QPixmap("./assets/icon.png");
	icon_pix = icon_pix.scaledToHeight(80);
	icon_pix = icon_pix.scaledToWidth(80);

	QLabel* icon_label = new QLabel();
	icon_label->setPixmap(icon_pix);

	title_layout->addStretch(15);
	title_layout->addWidget(icon_label);
	title_layout->addStretch(2);
	title_layout->addWidget(title_label);
	title_layout->addStretch(15);
	//title setting done;

	//setting main UI
	// & button slot connection
	main->setStyleSheet("QPushButton{ background-color: #c6ffcf;font:20pt}");
	int seat[] = { 0,
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
				  1,1,1,1,1,1,1,1,1,1,1,1, };

	QGridLayout* grid_seat = new QGridLayout;

	int id = 1;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (j == 6) { //represents reading room's aisle
				grid_seat->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum), i, j);
			}
			if (seat[12 * i + j + 1] == 1) {
				p_seat[id] = new QPushButton(QString::number(id));
				connect(p_seat[id], SIGNAL(clicked()), this, SLOT(seat_button_click()));

				p_seat[id]->setObjectName(QString::number(id)); //setting QPushbutton objects' name as seat number
				p_seat[id]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

				if (j >= 6) {
					grid_seat->addWidget(p_seat[id], i, j + 1);
				}
				else {
					grid_seat->addWidget(p_seat[id], i, j);
				}
				id += 1;
			}
		}
	}
	//main seat UI setting done;

	//<sidebar setting>
	//side bar button setup
	QPushButton* pause_btn = new QPushButton("Pause");
	pause_btn->setObjectName("pause_btn");
	QPushButton* renew_btn = new QPushButton("Renew");
	renew_btn->setObjectName("renew_btn");
	QPushButton* move_btn = new QPushButton("Move Seat");
	move_btn->setObjectName("move_btn");
	QPushButton* signup_btn = new QPushButton("Sign up");
	signup_btn->setObjectName("signup_btn");
	QPushButton* admin_btn = new QPushButton("Admin Login");
	admin_btn->setObjectName("admin_btn");
	QPushButton* return_btn = new QPushButton("Return");
	return_btn->setObjectName("return_btn");

	auto pause_btn_sty = "font: 20pt; background-color : #fff8a6;"
		"color:#252525; border: 4px solid #eae393;";
	auto renew_btn_sty = "font: 20pt; background-color : #ffd19a;"
		"color:#252525; border: 4px solid #e0b98d;";
	auto move_btn_sty = "font: 20pt; background-color : #ffc5a1;"
		"color:#252525; border: 4px solid #e5b192;";
	auto signup_btn_sty = "font: 20pt; background-color : #b0deff;"
		"color:#252525; border: 4px solid #a3c8e2;";
	auto admin_btn_sty = "font: 20pt; background-color : #5c5757;"
		"color:#363434; border: 4px solid #363434;";
	auto return_btn_sty = "font: 20pt; background-color : #8cb8ff;"
		"color:#252525; border: 4px solid #5e9cff;";

	auto prefer = QSizePolicy::Preferred;
	pause_btn->setSizePolicy(prefer, prefer);
	renew_btn->setSizePolicy(prefer, prefer);
	move_btn->setSizePolicy(prefer, prefer);
	signup_btn->setSizePolicy(prefer, prefer);
	return_btn->setSizePolicy(prefer, prefer);
	admin_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

	pause_btn->setStyleSheet({ pause_btn_sty });
	renew_btn->setStyleSheet({ renew_btn_sty });
	move_btn->setStyleSheet({ move_btn_sty });
	signup_btn->setStyleSheet({ signup_btn_sty });
	admin_btn->setStyleSheet({ admin_btn_sty });
	return_btn->setStyleSheet({ return_btn_sty });

	//side bar info setup
	QLabel* info_name = new QLabel(QString::fromLocal8Bit("생활관자치위원회"));
	info_name->setAlignment(Qt::AlignCenter);
	QLabel* info_contributor = new QLabel("Contributor : OOP Team");
	info_contributor->setAlignment(Qt::AlignRight);
	//할것 style 추가

	//side bar layout setup
	//button add to the layout
	QVBoxLayout* side_bar = new QVBoxLayout;
	side_bar->addWidget(pause_btn);
	side_bar->addWidget(renew_btn);
	side_bar->addWidget(move_btn);
	side_bar->addWidget(return_btn);
	side_bar->addWidget(signup_btn);

	//info add to the layout
	side_bar->addWidget(info_name);
	side_bar->addSpacing(30);
	side_bar->addWidget(info_contributor);
	side_bar->addSpacing(40);
	side_bar->addWidget(admin_btn); //admin login button to the bottom of the side bar
	//</sidebar setting>

	//<whole layout setting>

	whole->addLayout(title_layout, 0, 0);
	whole->addLayout(grid_seat, 1, 0);
	whole->addLayout(side_bar, 0, 1, 2, 1);

	main->setLayout(whole);
	setCentralWidget(main);
	//</whole layout setting>

	//<button-slot connection>
	connect(pause_btn, SIGNAL(clicked()), this, SLOT(pause_button_click()));
	connect(renew_btn, SIGNAL(clicked()), this, SLOT(renew_button_click()));
	connect(move_btn, SIGNAL(clicked()), this, SLOT(move_button_click()));
	connect(return_btn, SIGNAL(clicked()), this, SLOT(return_button_click()));

	connect(signup_btn, SIGNAL(clicked()), this, SLOT(signup_button_click()));
	connect(admin_btn, SIGNAL(clicked()), this, SLOT(admin_button_click()));


	//</button-slot connection>

	//Timer setup, it will call slot for every minutes.
	m_pTimer = new QTimer();
	m_pTimer->start(1000 * 60);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(minute()));

}

//slot for seat button
void BiseulReadingRoomReservation::seat_button_click()
{
	//seder() to get which button called the function
	QObject* obj = sender();
	int num = obj->objectName().toInt(); //getting seat number
	_set_occupied_style(num);
	
	if (exe_seat_manager.seat_status_check(num) == biseul_rroom::SeatStatus::Vacant) { // Vacant Button click
		int rfid_id = 0;//할것:rfid tag window


		biseul_rroom::UserAction action = exe_user_manager.user_valid_check(rfid_id);
		if (action == biseul_rroom::UserAction::Pass) {
			//reserve seat
			int hour = exe_user_manager.available_reserve_hour(rfid_id);
			int pause = exe_user_manager.get_user_pause_left(rfid_id);
			biseul_rroom::Seat* new_seat = exe_seat_manager.create_seat(rfid_id, hour, pause);
			exe_seat_manager.reserve_seat(num, new_seat);
			
			//할것: 그사람 몇번 경고 먹었는지도 알려줘야댐
			msgBox.setText(QString::fromLocal8Bit("성공적으로 자리를 예약하였습니다! Success!"));
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.show();
			
		}
		else if (action == biseul_rroom::UserAction::Signup) {
			msgBox.setText("회원가입이 되어있지 않습니다! 회원가입 후 이용해주세요\nUser not Signed Up! Please register first.");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.show();
		}
		else if (action == biseul_rroom::UserAction::Warning) {
			msgBox.setText("경고 횟수 누적으로 사용이 제한되었습니다.\nYou are banned because of warnings.");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.show();
		}
		else if (action == biseul_rroom::UserAction::OverTime) {
			msgBox.setText("오늘의 예약 횟수를 이미 소진하였습니다.\nYou already used all of your reservation times per day");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.show();
		}

	}
	else { //not vacant button
		//info window 
	}
	
}

void BiseulReadingRoomReservation::pause_button_click()
{
	//할것:rfid tag window
	__int64 rfid_id = 0;

	int num = exe_seat_manager.find_seat(rfid_id); //num as seat number
	if (num == -1) { //seat doesn't exist
		msgBox.setText("예약되어있지 않습니다. Not reserved.");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.show();
	}
	else {
		exe_seat_manager.pause_seat(num);
		msgBox.setText("자리비움 처리 되었습니다. Paused your seat.");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.show();
	}
}

void BiseulReadingRoomReservation::renew_button_click()
{
	


}

void BiseulReadingRoomReservation::move_button_click()
{
	
}

void BiseulReadingRoomReservation::return_button_click()
{
	

}

void BiseulReadingRoomReservation::signup_button_click()
{
	RegisterPanel rp;
	if (rp.exec() == QDialog::Accepted) {

	}

}

void BiseulReadingRoomReservation::admin_button_click()
{
	AdminPanel admin_panel;
	admin_panel.exec();
}

void BiseulReadingRoomReservation::minute_tiemout()
{
}


//setting seat buttons' style
void BiseulReadingRoomReservation::_set_vacant_style(int num)
{
	this->p_seat[num]->setStyleSheet({ "background-color: #c6ffcf;font:20pt" });

}

void BiseulReadingRoomReservation::_set_occupied_style(int num)
{
	this->p_seat[num]->setStyleSheet({ "background-color: red; font:20pt" });
}

void BiseulReadingRoomReservation::_set_paused_style(int num)
{
	this->p_seat[num]->setStyleSheet({ "background-color: yellow; font:20pt" });
}
