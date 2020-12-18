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
    img = new QLabel();
    QPixmap p = QPixmap("./assets/tagging.png");
    img->setPixmap(p);
    img->setStyleSheet({ "border: 0px;" });

    // cancel button
    cancel_button = new QPushButton("Cancel");
    cancel_button->setFocusPolicy(Qt::NoFocus);
    cancel_button->setStyleSheet({ "background-color: white; border: 1.5px solid; padding: 5px; border-color: black;" });
    connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel()));

    main_grid = new QGridLayout;
    main_grid->addWidget(img, 0, 0, 2, 2);
    main_grid->addWidget(cancel_button, 3, 1, 1, 1);
    main_grid->setAlignment(Qt::AlignCenter);

    setWindowFlags(Qt::FramelessWindowHint); //프레임 제거
    setFixedSize(400, 400);
    setModal(true);
    setLayout(main_grid);

    }

RfidPanel::~RfidPanel()
{
    delete img;
    delete cancel_button;
    delete main_grid;
    delete ui;
}

void RfidPanel::cancel() {
    int_number = -1;
    this->close();
}


void RfidPanel::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_0) {
        rfid_str.append(QString::number(0));
    }
    else if (event->key() == Qt::Key_1) {
        rfid_str.append(QString::number(1));
    }
    else if (event->key() == Qt::Key_2) {
        rfid_str.append(QString::number(2));
    }
    else if (event->key() == Qt::Key_3) {
        rfid_str.append(QString::number(3));
    }
    else if (event->key() == Qt::Key_4) {
        rfid_str.append(QString::number(4));
    }
    else if (event->key() == Qt::Key_5) {
        rfid_str.append(QString::number(5));
    }
    else if (event->key() == Qt::Key_6) {
        rfid_str.append(QString::number(6));
    }
    else if (event->key() == Qt::Key_7) {
        rfid_str.append(QString::number(7));
    }
    else if (event->key() == Qt::Key_8) {
        rfid_str.append(QString::number(8));
    }
    else if (event->key() == Qt::Key_9) {
        rfid_str.append(QString::number(9));
    }
    else if (event->key() == Qt::Key_Return) {
        string_number = rfid_str.toStdString();
        int_number = std::stoll(string_number);
        this->accept();
    }
    else {
            
    }

}