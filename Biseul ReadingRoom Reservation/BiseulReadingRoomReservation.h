#pragma once

#include <QtWidgets/QMainWindow>
#include <QInputDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QString>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpacerItem>
#include <QPainter>
#include <QMessageBox>
#include <QTimer>

#include "ui_BiseulReadingRoomReservation.h"

#include "AdminPanel.h"
#include "RfidPanel.h"
#include "RegisterPanel.h"
#include "SeatInfoPanel.h"

#include "DBinterface.h"
#include "DBsystem.h"

#include "Reserver.h"
#include "Manager.h"
#include "SeatManager.h"
#include "UserManager.h"
#include "TimeManager.h"

class BiseulReadingRoomReservation : public QMainWindow
{
    Q_OBJECT

public:
    BiseulReadingRoomReservation(QWidget *parent = Q_NULLPTR);
    friend class AdminPanel; //AdminPanel class to be a friend --> to access seatmanager, etc

    __int64 tag_rfid();

private slots:
    void seat_button_click();

    void pause_button_click();
    void renew_button_click();
    void move_button_click();
    void return_button_click();

    void signup_button_click();
    void admin_button_click();

    void minute_timeout();

private:

    Ui::BiseulReadingRoomReservationClass ui;
    QGridLayout* whole;
    QWidget* main;

    void _set_vacant_style(int num);
    void _set_occupied_style(int num);
    void _set_paused_style(int num);

    void _msg_not_reserved();
    void _msg_already_reserved();
    void _msg_diy(const char* msg);

    
    //managers are created with singletons
    biseul_rroom::SeatManager exe_seat_manager = biseul_rroom::SeatManager::instance();
    biseul_rroom::UserManger exe_user_manager = biseul_rroom::UserManger::instance();
    biseul_rroom::TimeManager exe_time_manager = biseul_rroom::TimeManager::instance();

    //DBinterface
    biseul_rroom::DBinterface* biseul_db_interface = new biseul_rroom::DBinterface("./data/test111.db");
    
    QTimer* m_pTimer;
    QMessageBox msgBox;
    QPushButton* p_seat[125];

};


