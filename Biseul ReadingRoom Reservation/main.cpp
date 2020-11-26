#include "BiseulReadingRoomReservation.h"
#include "BiseulReadingRoomReservation_log.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BiseulReadingRoomReservation w;
    w.show();

    log_init();

    write_log("info1");
    write_log("info2");

    return a.exec();
}
