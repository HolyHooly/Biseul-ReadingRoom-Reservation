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
    // ����
    QLabel *label;
    // ���
    QTextBrowser *brouser;
    // ��� ������ layout, ��� �Ƚᵵ �ɵ�
    QHBoxLayout *hlayout1;
    QHBoxLayout *hlayout2;
    QHBoxLayout *hb_con;
    QVBoxLayout *hh_con;
    QVBoxLayout *button_con;
    // �̸�, �й� �Է¶�
    QLineEdit *input_name;
    QLineEdit *input_number;
    // Ȯ��, ��ҹ�ư
    QPushButton *confirm;
    QPushButton *nono;
};

#endif // MYDIALOG_H
