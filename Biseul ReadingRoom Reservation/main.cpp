#include <QtWidgets/QApplication>
#include <QFont>

#include "BiseulReadingRoomReservation.h"
#include "BiseulReadingRoomReservation_log.h"

#include "DBInterface.h"
#include "DBsystem.h"

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    QFont font;
    font.setFamily(QString("Godo B"));
    a.setFont(font);
    BiseulReadingRoomReservation w;

    w.show();

    return a.exec();
}
