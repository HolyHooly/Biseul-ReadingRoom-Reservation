#ifndef TIMER_H
#define TIMER_H

#include <QDialog>
#include <QWidget>
#include <QFont>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qdatetime.h>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class Timer;
}

class Timer : public QDialog
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();
    QDialog *aa;
    void Add();
    void Init();

private slots:
//    void timerEvent();
//    void timerStop();
//    void timerStart();
//    void timerInit();
//    void paintEvent(QPaintEvent *);

    void Minus();
    void Update();

private:
    Ui::Timer *ui;
//    QTimer *timer;
//    QLabel *label;
//    QTime *time;
//    QTimer* tr1;
//    QTime* t1;
//    QTime* t2;
//    QTime* n;
//    QPushButton* bt1;
//    QPushButton* bt2;
//    QPushButton* bt3;
//    QPushButton* bt4;

    QTime t_init;
    QTimer *timer;

protected:
    int t_count;
    QString show_time;
    QLabel *s;

};

#endif // TIMER_H
