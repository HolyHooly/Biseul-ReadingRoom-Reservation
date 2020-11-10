#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BiseulReadingRoomReservation.h"
//test3
class BiseulReadingRoomReservation : public QMainWindow
{
    Q_OBJECT

public:
    BiseulReadingRoomReservation(QWidget *parent = Q_NULLPTR);

private:
    Ui::BiseulReadingRoomReservationClass ui;
};
