#include <QtWidgets/QApplication>

#include "BiseulReadingRoomReservation.h"
#include "BiseulReadingRoomReservation_log.h"

#include "DBInterface.h"
#include "DBsystem.h"

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    BiseulReadingRoomReservation w;

    w.show();

    return a.exec();
}
