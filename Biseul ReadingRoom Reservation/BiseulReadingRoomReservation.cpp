﻿
#include "BiseulReadingRoomReservation.h"
#include <fstream>
#include <iostream>
#include <string>

BiseulReadingRoomReservation::BiseulReadingRoomReservation(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this); //default setup

	whole = new QGridLayout;
	main = new QWidget;
	setStyleSheet({ "background-color:rgb(255,255,255);" });
	setMenuBar(false);
	setWindowFlags(Qt::FramelessWindowHint);

//---------------------title layout---------------------------------//

	QHBoxLayout* title_layout = new QHBoxLayout;
	QLabel* title_label = new QLabel(QString::fromLocal8Bit("비슬빌리지 독서실 예약시스템"));
	auto sty_t = "font: 20pt Godo B;";
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

//------------------setting main UI---------------------------------//
	// & button slot connection
	main->setStyleSheet("QPushButton{background-color : #d6f7ad; color:#1d7f46; border:3px solid #bdd899; font: 75 14pt; min-width: 80px;}");
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
				p_seat[id]->setObjectName(QString::number(id)); //setting QPushbutton objects' name as seat number
				p_seat[id]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
				connect(p_seat[id], SIGNAL(clicked()), this, SLOT(seat_button_click()));

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

//--------------------<sidebar setting>------------------------//
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
	//side bar button style
	auto pause_btn_sty = "font: 20pt Godo B; background-color : #fff8a6;"
		"color:#252525; border: 4px solid #eae393;";
	auto renew_btn_sty = "font: 20pt Godo B; background-color : #ffd19a;"
		"color:#252525; border: 4px solid #e0b98d;";
	auto move_btn_sty = "font: 20pt Godo B; background-color : #ffc5a1;"
		"color:#252525; border: 4px solid #e5b192;";
	auto signup_btn_sty = "font: 20pt Godo B; background-color : #8cb8ff;"
		"color:#252525; border: 4px solid #5e9cff;";
	auto admin_btn_sty = "font: 20pt Godo B; background-color : #5c5757;"
		"color:#363434; border: 4px solid #363434;";
	auto return_btn_sty = "font: 20pt Godo B; background-color : #b0deff;"
		"color:#252525; border: 4px solid #a3c8e2;";

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
	QLabel* info_contributor = new QLabel(QString::fromLocal8Bit("Contributor \n 김태현, 고지연, 이준영, 박준서"));
	info_name->setAlignment(Qt::AlignCenter);
	info_contributor->setAlignment(Qt::AlignRight);
	auto sty_con = "font: 63 10pt Godo B";
	info_contributor->setStyleSheet(sty_con);
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
//---------------------------------------------------//

//--------------<button-slot connection>-------------------//
	connect(pause_btn, SIGNAL(clicked()), this, SLOT(pause_button_click()));
	connect(renew_btn, SIGNAL(clicked()), this, SLOT(renew_button_click()));
	connect(move_btn, SIGNAL(clicked()), this, SLOT(move_button_click()));
	connect(return_btn, SIGNAL(clicked()), this, SLOT(return_button_click()));

	connect(signup_btn, SIGNAL(clicked()), this, SLOT(signup_button_click()));
	connect(admin_btn, SIGNAL(clicked()), this, SLOT(admin_button_click()));
//----------------</button-slot connection>----------------//

	//Timer setup, it will call slot for every minutes.
	m_pTimer = new QTimer();
	m_pTimer->start(1000 * 60); //1000ms * 60s
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(minute_timeout()));


	showMaximized();

	init_logging();

	std::string log = "Program booted";
	write_log(log);

}

void BiseulReadingRoomReservation::minute_timeout()
{
	if (exe_time_manager.is_time(7, 0)) { //is time 7:00 am
		exe_user_manager.reset_all();
		exe_seat_manager.reset_all();
	}
	
	//PART1과 PART2는 독서실 정책에 맞게 수정하면 됨

	for (int i = 1; i <= READINGROOM_SEAT; ++i) { //investigating all seats
		biseul_rroom::Seat* cur_seat = exe_seat_manager.get_seat(i);
		if (cur_seat != nullptr) { //seat not vacant
			if (exe_seat_manager.seat_status_check(i) == biseul_rroom::SeatStatus::Paused) { //if seat is on paused state
				cur_seat->minus_pause_time(); //1 min minus of pause time
				if (cur_seat->get_pause_time() < 0) { //pause time over
					//PART 1
					int stud_id = cur_seat->get_reserver()->get_stud_id(); // get seat reserver's student id
					biseul_db_interface->give_penalty(stud_id); //give him/her a penalty
					exe_seat_manager.return_seat(i); //return the seat
					_set_vacant_style(i);
					continue;
				}
			}
			if (cur_seat->over_time()) { //check if current seat over time
				//PART 2
				int stud_id = cur_seat->get_reserver()->get_stud_id(); // get seat reserver's student id
				biseul_db_interface->give_penalty(stud_id); //give him/her a penalty
				exe_seat_manager.return_seat(i); //return the seat
				_set_vacant_style(i);
				continue;
			}
		}
	}

}

//slot for seat button
void BiseulReadingRoomReservation::seat_button_click()
{
	//seder() to get which button called the function
	QObject* obj = sender();
	int num = obj->objectName().toInt(); //getting seat number
	
	if (exe_seat_manager.seat_status_check(num) == biseul_rroom::SeatStatus::Vacant) { // Vacant Button click
		
		__int64 rfid_id = tag_rfid(); //Getting RFID information with RfidPanel
		if (rfid_id == -1) { //user cancelled the action (do nothing)
		}
		else {
			//User inquiry start
			biseul_rroom::UserAction action = exe_user_manager.user_valid_check(rfid_id, biseul_db_interface);

			if (action == biseul_rroom::UserAction::Pass) { //User is able to reserve a seat
				if (exe_seat_manager.find_seat(rfid_id) != -1) { // Already taken a seat (double reservation trial)
					_msg_already_reserved(); //message box
				}
				else { //none of already taken seat
					//get user's available time data
					int hour = exe_user_manager.available_reserve_hour(rfid_id);
					int pause = exe_user_manager.get_user_pause_left(rfid_id);
					
					//get user's basic information from the db
					std::string name;
					std::string* nameptr = &name;
					int stud_id;
					int warnings;
					biseul_db_interface->get_studinf_byrfid(nameptr, stud_id, rfid_id, warnings);

					exe_seat_manager.reserve_seat(num, name, stud_id, rfid_id, hour, pause);
					exe_user_manager.add_user_reserve_cnt(rfid_id);


					_msg_diy("성공적으로 자리를 예약하였습니다! Success!");
					std::string log = "Reserve Trial, Success: ";
					log += std::to_string(rfid_id) + ", " + std::to_string(num) + "번 좌석";
					write_log(log);

					char msg[] = "회 경고횟수가 존재합니다! 주의바랍니다.\nYour have warnings. Be careful.";
					std::string buf = "";
					char str[20];
					buf += itoa(warnings, str, 10);
					buf += msg;
					const char* final_msg = buf.c_str();

					if (warnings > 0) {
						_msg_diy(final_msg);
					}
					_set_occupied_style(num);
				}

			}
			else if (action == biseul_rroom::UserAction::Signup) {
				_msg_diy("회원가입이 되어있지 않습니다! 회원가입 후 이용해주세요\nUser not Signed Up! Please register first.");
				std::string log = "Reserve Trial, Not Registered: ";
				log += std::to_string(rfid_id) + ", " + std::to_string(num) + "번 좌석";
				write_log(log);
			}
			else if (action == biseul_rroom::UserAction::Warning) {
				_msg_diy("경고 횟수 누적으로 사용이 제한되었습니다.\nYou are banned because of warnings.");
				std::string log = "Reserve Trial, Banned: ";
				log += std::to_string(rfid_id) + ", " + std::to_string(num) + "번 좌석";
				write_log(log);
			}
			else if (action == biseul_rroom::UserAction::OverTime) {
				_msg_diy("오늘의 예약 횟수를 이미 소진하였습니다.\nYou already used all of your reservation times per day");
				std::string log = "Reserve Trial, Taken all reserve cnt: ";
				log += std::to_string(rfid_id) + ", " + std::to_string(num) + "번 좌석";
				write_log(log);
			}
		}
	}
	else { //if pressed occupied seat

		biseul_rroom::Seat* cur_seat = exe_seat_manager.get_seat(num);
		std::string temp_name = cur_seat->get_reserver()->get_name();
		tm* reserved_time = cur_seat->get_reserved_time();
		tm* end_time = cur_seat->get_reserve_end_time();
		int pause_time = cur_seat->get_pause_time();
		SeatInfoPanel sp(this, num, temp_name, reserved_time, end_time, pause_time);
		sp.exec();

	}
}

void BiseulReadingRoomReservation::pause_button_click()
{
	__int64 rfid_id = tag_rfid();
	if (rfid_id == -1) { //user cancelled the action
	}
	else {
		int num = exe_seat_manager.find_seat(rfid_id); //num as seat number
		if (num == -1) { //seat doesn't exist
			_msg_not_reserved();
		}
		else {
			biseul_rroom::Seat* cur_seat = exe_seat_manager.get_seat(num);
			if (cur_seat->get_status() == biseul_rroom::SeatStatus::Occupied) { //seat is occupied
				if (cur_seat->get_pause_time() <= 0) { //not enough pause time
					_msg_diy("자리비움 시간이 남아있지 않습니다. Not enough out time.");
					std::string log = "Pause Trial, No time left: ";
					log += std::to_string(rfid_id) + ", " + std::to_string(num) + "번 좌석";
					write_log(log);
				}
				else { //enough pause time
					exe_seat_manager.pause_seat(num);
					_msg_diy("자리비움 처리 되었습니다. Out your seat.");
					std::string log = "Pause Trial, Success: ";
					log += std::to_string(rfid_id) + ", " + std::to_string(num) + "번 좌석";
					write_log(log);
					_set_paused_style(num);
				}
			}
			else {
				exe_seat_manager.unpause_seat(num);
				_msg_diy("자리비움 해제 되었습니다. In your seat.");
				std::string log = "Unpause Trial, Success: ";
				log += std::to_string(rfid_id) + ", " + std::to_string(num) + "번 좌석";
				write_log(log);
				_set_occupied_style(num);
			}
		}
	}
}

void BiseulReadingRoomReservation::renew_button_click()
{
	__int64 rfid_id = tag_rfid();
	if (rfid_id == -1) { //user cancelled the action
	}
	else {
		int seat_num = exe_seat_manager.find_seat(rfid_id);
		if (seat_num == -1) {
			_msg_not_reserved();
		}
		else {
			//only able to renew before 30min of reserve end time
			if (exe_seat_manager.get_seat(seat_num)->before_minutes(30)) {
				exe_seat_manager.renew_seat(seat_num, 3); //add 3hours to the seat
				_msg_diy("3시간 연장되었습니다! Renewed your seat for 3 hours!");
				std::string log = "Renew Trial, Success: ";
				log += std::to_string(rfid_id) + ", " + std::to_string(seat_num) + "번 좌석";
				write_log(log);
			}
			else {
				_msg_diy("종료 30분 전부터 연장할 수 있습니다!\nAble to renew before 30min to the end!");
				std::string log = "Renew Trial, Not yet: ";
				log += std::to_string(rfid_id) + ", " + std::to_string(seat_num) + "번 좌석";
				write_log(log);
			}
		}
	}
}

void BiseulReadingRoomReservation::move_button_click()
{
	__int64 rfid_id = tag_rfid();
	if (rfid_id == -1) { //user cancelled tagging rfid
	}
	else {
		int seat_num = exe_seat_manager.find_seat(rfid_id);
		if (seat_num == -1) { //cannot find seat reserved
			_msg_not_reserved();
		}
		else {
			bool ok;
			int to_seat_num = QInputDialog::getInt(this, tr("Where to Move?"), tr("To: "), 1, 1, READINGROOM_SEAT, 1, &ok);
			if (ok) { //user pressed ok (not cancel)
				if (exe_seat_manager.get_seat(to_seat_num)==nullptr) { //seat is empty
					exe_seat_manager.move_seat(seat_num, to_seat_num);
					_set_vacant_style(seat_num);
					_set_occupied_style(to_seat_num);
					_msg_diy("자리를 이동했습니다! Moved your seat!");
					std::string log = "Move Trial, Success: ";
					log += std::to_string(rfid_id) + ", " + std::to_string(seat_num) + "번 --> " + std::to_string(to_seat_num);
					write_log(log);
				}
				else {
					_msg_diy("빈 자리를 선택해주세요! Please choose vacant seat!");
				}
			}
		}
	}
}

void BiseulReadingRoomReservation::return_button_click()
{
	__int64 rfid_id = tag_rfid();
	if (rfid_id == -1) { //user cancelled the action
	}
	else {
		int seat_num = exe_seat_manager.find_seat(rfid_id);
		if (seat_num == -1) {
			_msg_not_reserved();
		}
		else {
			exe_seat_manager.return_seat(seat_num);
			_msg_diy("반납되었습니다! Returned your seat!");
			std::string log = "Return Trial, Success: ";
			log += std::to_string(rfid_id) + ", " + std::to_string(seat_num) + "번 좌석";
			write_log(log);
			_set_vacant_style(seat_num);
		}
	}
}

void BiseulReadingRoomReservation::signup_button_click()
{
	RegisterPanel rp;
	if (rp.exec() == QDialog::Accepted) {
		std::string name = rp.get_name();
		__int64 rfid_id = rp.get_rfid();
		int stud_id = rp.get_stud_id();

		if (biseul_db_interface->existence_check(stud_id) ||
			biseul_db_interface->existence_check_byrfid(rfid_id))
		{ //already have a record on db
			_msg_diy("이미 가입되어있습니다! Already registered!");
			std::string log = "Signup Trial, Already: ";
			log += std::to_string(rfid_id);
			write_log(log);
		}
		else {
			if (biseul_db_interface->insert(&name, stud_id, rfid_id)) { //학생 정보 db에 insert
				_msg_diy("가입이 완료되었습니다! Registered!");
				std::string log = "Signup Trial, Success: ";
				log += std::to_string(rfid_id);
				write_log(log);
			}
			else { //insert 실패시
				_msg_diy("알 수 없는 에러가 발생하였습니다! 관리자에게 문의하세요.\nError! Please contact the administrator");
				std::string log = "Signup Trial, Unknown Error Occur: ";
				log += std::to_string(rfid_id);
				write_log(log);
			}
		}
	}
}

void BiseulReadingRoomReservation::admin_button_click()
{
	//admin login
	__int64 rfid_id = tag_rfid();
	int flag = 0;
	if (rfid_id == -1) { //user cancelled
	}
	else {
		std::string in_line;
		std::ifstream in("./data/admin.txt");
		while (std::getline(in, in_line)) {
			const char* line = in_line.c_str();
			if (rfid_id == _atoi64(line)) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			std::string log = "Admin Login Trial, Success: ";
			log += std::to_string(rfid_id);
			write_log(log);
			AdminPanel admin_panel(nullptr,exe_seat_manager);
			admin_panel.exec();
			refresh();
		}
		else {
			_msg_diy("관리자가 아닙니다!");
			std::string log = "Admin Login Trial, Not admin: ";
			log += std::to_string(rfid_id);
			write_log(log);
		}
	}
}



BiseulReadingRoomReservation::~BiseulReadingRoomReservation()
{
	std::string log = "Program Terminated";
	write_log(log);
}

__int64 BiseulReadingRoomReservation::tag_rfid()
{
	RfidPanel rf;
	__int64 rfid_id;
	if (rf.exec() == QDialog::Accepted) {
		rfid_id = rf.getdata();
		return rfid_id;
	}
	else return -1;
}

void BiseulReadingRoomReservation::_msg_not_reserved()
{
	msgBox.setText(QString::fromLocal8Bit("자리가 예약되어있지 않습니다! Not reserved a seat!"));
	msgBox.setStyleSheet({ "font: 75 10pt Godo M;" });
	msgBox.setWindowTitle("Error");
	msgBox.setWindowIcon(QIcon("./assets/icon.png"));
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.show();
}
void BiseulReadingRoomReservation::_msg_already_reserved()
{
	msgBox.setText(QString::fromLocal8Bit("이미 자리를 예약하였습니다! Already reserved a seat!"));
	msgBox.setStyleSheet({ "font: 75 10pt Godo M;" });
	msgBox.setWindowTitle("Error");
	msgBox.setWindowIcon(QIcon("./assets/icon.png"));
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.show();
}
void BiseulReadingRoomReservation::_msg_diy(const char* msg)
{
	msgBox.setText(QString::fromLocal8Bit(msg));
	msgBox.setStyleSheet({ "font: 75 10pt Godo M;" });
	msgBox.setWindowTitle("Alert");
	msgBox.setWindowIcon(QIcon("./assets/icon.png"));
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.show();

}

void BiseulReadingRoomReservation::refresh() {
	
	for (int i = 1; i <= READINGROOM_SEAT; ++i) {
		auto cur_status = exe_seat_manager.seat_status_check(i);
		if (cur_status == biseul_rroom::SeatStatus::Vacant) {
			_set_vacant_style(i);
		}
		else if (cur_status == biseul_rroom::SeatStatus::Occupied) {
			_set_occupied_style(i);
		}
		else if (cur_status == biseul_rroom::SeatStatus::Paused) {
			_set_paused_style(i);
		}
	}
}



//setting seat buttons' style
void BiseulReadingRoomReservation::_set_vacant_style(int num)
{
	this->p_seat[num]->setStyleSheet({ "background-color : #d6f7ad; color:#1d7f46; border:3px solid #bdd899; font: 75 14pt Godo B; min-width: 80px;; qproperty-iconSize: 0px 0px" });

}
void BiseulReadingRoomReservation::_set_occupied_style(int num)
{
	this->p_seat[num]->setStyleSheet({ "background-color: #f38181;border:3px solid #d37272; font: 75 14pt Godo B; qproperty-icon: url(./assets/occupied.png); qproperty-iconSize: 15px 15px;" });
}
void BiseulReadingRoomReservation::_set_paused_style(int num)
{
	this->p_seat[num]->setStyleSheet({ "background-color: #fee9b2; border:3px solid #e2d0a1; font: 75 14pt Godo B;qproperty-icon: url(./assets/flag.png); qproperty-iconSize: 20px 20px; " });
}