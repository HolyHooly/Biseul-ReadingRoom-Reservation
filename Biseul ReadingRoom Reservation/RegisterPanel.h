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
    std::string get_name();
    int get_stud_id();

private slots:
    void cancel();
    void confirm();

private:

    Ui::RegisterPanel *ui;
    
    QLabel *label; // 제목
    QTextBrowser *browser; // 약관
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
    std::string name;
    int stud_id;

    // 확인, 취소버튼
    QPushButton *confirm_btn;
    QPushButton *cancel_btn;
};

#endif // MYDIALOG_H
