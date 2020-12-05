#include "RfidPanel.h"
#include "ui_RfidPanel.h"

#include <QString>


RfidPanel::RfidPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RfidPanel)
{
    ui->setupUi(this);
    setStyleSheet({ "background-color:rgb(255,255,255);" });

    // images
    im = new QLabel();
    QPixmap p = QPixmap("./assets/tagging.png");
    im->setPixmap(p);
    im->setStyleSheet({ "border: 0px;" });

    // cancel button
    n = new QPushButton("Cancel");
    n->setFocusPolicy(Qt::NoFocus);
    n->setStyleSheet({ "background-color: white; border: 1.5px solid; padding: 5px; border-color: black;" });

    grid = new QGridLayout;
    grid->addWidget(im, 0, 0, 2, 2);
    grid->addWidget(n, 3, 1, 1, 1);
    grid->setAlignment(Qt::AlignCenter);

    setWindowFlags(Qt::FramelessWindowHint); //프레임 제거
    setFixedSize(400, 400);
    setModal(true);
    setLayout(grid);

    connect(n, SIGNAL(clicked()), this, SLOT(cancel()));

    }

RfidPanel::~RfidPanel()
{
    delete ui;
}

void RfidPanel::cancel() {
    int_number = -1;
    this->close();
}


void RfidPanel::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_0) {
        rfid.append(QString::number(0));
    }
    else if (event->key() == Qt::Key_1) {
        rfid.append(QString::number(1));
    }
    else if (event->key() == Qt::Key_2) {
        rfid.append(QString::number(2));
    }
    else if (event->key() == Qt::Key_3) {
        rfid.append(QString::number(3));
    }
    else if (event->key() == Qt::Key_4) {
        rfid.append(QString::number(4));
    }
    else if (event->key() == Qt::Key_5) {
        rfid.append(QString::number(5));
    }
    else if (event->key() == Qt::Key_6) {
        rfid.append(QString::number(6));
    }
    else if (event->key() == Qt::Key_7) {
        rfid.append(QString::number(7));
    }
    else if (event->key() == Qt::Key_8) {
        rfid.append(QString::number(8));
    }
    else if (event->key() == Qt::Key_9) {
        rfid.append(QString::number(9));
    }
    else if (event->key() == Qt::Key_Return) {
        string_number = rfid.toStdString();
        int_number = std::stoll(string_number);
        this->accept();
    }
    else {
            
    }

}