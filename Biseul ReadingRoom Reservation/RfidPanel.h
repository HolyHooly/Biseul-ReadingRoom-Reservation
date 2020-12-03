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
    
    QMessageBox msg;// 예, 아니오 뜨는 msg
    QLabel *im;// 메인 이미지
    QPushButton *n;// 취소 버튼
    QGridLayout *grid; // grid

    QString rfid;// rfid를 append 시킬 장소
    __int64 int_number;// 들어온 사용자의 rfid number
    std::string string_number;// rfid를 string으로 받고 싶으면 이거 사용

protected:
   
    void keyPressEvent(QKeyEvent *event); // override

};

#endif // RFID_H
