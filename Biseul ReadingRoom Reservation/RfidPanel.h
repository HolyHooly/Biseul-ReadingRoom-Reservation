#ifndef RFID_H
#define RFID_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSize>

#include <QMessageBox>
#include <QKeyEvent>

namespace Ui {
class RfidPanel;
}

class RfidPanel : public QDialog
{
    Q_OBJECT

public:
    explicit RfidPanel(QWidget *parent = nullptr);
    ~RfidPanel();

    __int64 getdata() { return int_number; };
    

private slots:
    void cancel();

private:


    Ui::RfidPanel *ui;
    
    QMessageBox msg;// ��, �ƴϿ� �ߴ� msg
    QLabel *im;// ���� �̹���
    QPushButton *n;// ��� ��ư
    QGridLayout *grid; // grid

    QString rfid;// rfid�� append ��ų ���
    __int64 int_number;// ���� ������� rfid number
    std::string string_number;// rfid�� string���� �ް� ������ �̰� ���

protected:
   
    void keyPressEvent(QKeyEvent *event); // override

};

#endif // RFID_H
