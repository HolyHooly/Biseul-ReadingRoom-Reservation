#pragma once

#include <QtWidgets/QMainWindow>
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


#include "AdminPanel.h"
#include "RfidPanel.h"
//#include "RegisterPanel.h"
//#include "SeatInfoPanel.h"


#include "ui_BiseulReadingRoomReservation.h"

#include "Reserver.h"
#include "Manager.h"
#include "SeatManager.h"
#include "UserManager.h"
#include "TimeManager.h"

#include "DBInterface.h"
#include "DBsystem.h"

#define kor(str) QString::fromLocal8Bit(str)

class BiseulReadingRoomReservation : public QMainWindow
{
    Q_OBJECT

public:
    BiseulReadingRoomReservation(QWidget *parent = Q_NULLPTR);
    friend class AdminPanel; //AdminPanel class to be a friend --> to access seatmanager, etc

private slots:
    void seat_button_click();

    void pause_button_click();
    void renew_button_click();
    void move_button_click();
    void return_button_click();

    void signup_button_click();
    void admin_button_click();

    void minute_tiemout();

private:

    void _set_vacant_style(int num);
    void _set_occupied_style(int num);
    void _set_paused_style(int num);

    Ui::BiseulReadingRoomReservationClass ui;
    
    //managers are created with singletons
    biseul_rroom::SeatManager exe_seat_manager = biseul_rroom::SeatManager::instance();
    biseul_rroom::UserManger exe_user_manager = biseul_rroom::UserManger::instance();
    biseul_rroom::TimeManager exe_time_manager = biseul_rroom::TimeManager::instance();

    //DBinterface
    biseul_rroom::DBinterface* interface1 = new biseul_rroom::DBinterface("test111.db");
   

    //QTime* seat_time[125];
    QLabel* label_time;
    QTimer* m_pTimer;
    QMessageBox msgBox;
    QPushButton* p_seat[125];
    QGridLayout* whole;
    QWidget* main;
    int uss[125] = { 0, };

};


