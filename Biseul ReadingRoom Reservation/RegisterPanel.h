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

private slots:
    void cancel();
    void TAG();

private:
    Ui::RegisterPanel *ui;
    RfidPanel *rf;
    // 제목
    QLabel *label;
    // 약관
    QTextBrowser *brouser;
    // 약관 밑쪽의 layout, 상관 안써도 될듯
    QHBoxLayout *hlayout1;
    QHBoxLayout *hlayout2;
    QHBoxLayout *hb_con;
    QVBoxLayout *hh_con;
    QVBoxLayout *button_con;
    // 이름, 학번 입력란
    QLineEdit *input_name;
    QLineEdit *input_number;
    // 확인, 취소버튼
    QPushButton *confirm;
    QPushButton *nono;
};

#endif // MYDIALOG_H
