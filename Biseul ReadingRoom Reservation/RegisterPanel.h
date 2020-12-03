#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QString>
#include <QTextEdit>
#include <QLineEdit>
#include <QRegularExpressionValidator>

#include <fstream>

#include "RfidPanel.h"

namespace Ui {
class RegisterPanel;
}

class RegisterPanel : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterPanel(QWidget *parent = nullptr);
    ~RegisterPanel();

    __int64 get_rfid() { return rfid_id; };


   

private slots:
    void cancel();
    void TAG();

private:


    Ui::RegisterPanel *ui;
    RfidPanel *rf;
    
    QLabel *label; // 제목
    
    QTextBrowser *brouser; // 약관
    // 약관 밑쪽의 layout, 상관 안써도 될듯
    QHBoxLayout *hlayout1;
    QHBoxLayout *hlayout2;
    QHBoxLayout *hb_con;
    QVBoxLayout *hh_con;
    QVBoxLayout *button_con;

    // 이름, 학번 입력란
    QLineEdit *input_name;
    QLineEdit *input_number;
    __int64 rfid_id = 0;

    // 확인, 취소버튼
    QPushButton *confirm;
    QPushButton *nono;
};

#endif // MYDIALOG_H
