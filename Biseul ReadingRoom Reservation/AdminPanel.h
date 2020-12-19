

#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>

#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QTableView>
#include <QAbstractScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QSize>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSortFilterProxyModel>

#include "Manager.h"
#include "SeatManager.h"
#include "SeatSave.h"

namespace Ui {
    class AdminPanel;
}


class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent, biseul_rroom::SeatManager&);
    ~AdminPanel();
    
private slots:
    void seat_button_clicked();
    void return_box_clicked();
    void pause_box_clicked();
    void execute_button_clicked();

    void recent_button_clicked();
    void save_button_clicked();
    void exit_button_clicked();

private:
    Ui::AdminPanel* ui;
    QPushButton* s_seat[READINGROOM_SEAT+1]; //seat button ptr array
    biseul_rroom::SeatManager* exe_manager_ptr = nullptr;
    QButtonGroup box_group;

    QCheckBox* return_box = new QCheckBox(QString::fromLocal8Bit("반납"));
    QCheckBox* warning_box = new QCheckBox(QString::fromLocal8Bit("경고 추가"));
    QRadioButton* pause_box = new QRadioButton(QString::fromLocal8Bit("자리비움 설정/해제"));

    QSortFilterProxyModel* filter_model = new QSortFilterProxyModel();

    QString vacant_unchecked_style = "font: 16pt Godo B; background-color:rgb(255, 255, 255); color:rgb(0, 0, 0); border:1px solid black;";
    QString reserved_unchecked_style = "font: 16pt Godo B; background-color:rgb(255, 150, 152); color:rgb(0, 0, 0); border:1px solid black;";
    QString paused_unchecked_style = "font: 16pt Godo B; background-color:rgb(255, 245, 124); color:rgb(0, 0, 0); border:1px solid black;";
    QString vacant_checked_style = "font: 16pt Godo B; background-color:rgb(99, 99, 99); color:rgb(255, 255, 255); border:1px solid white;";
    QString reserved_checked_style = "font: 16pt Godo B; background-color:rgb(193, 88, 90); color:rgb(255, 255, 255); border:1px solid white;";
    QString paused_checked_style = "font: 16pt Godo B; background-color:rgb(218, 187, 6); color:rgb(255, 255, 255); border:1px solid white;";

};

#endif // ADMIN_H
