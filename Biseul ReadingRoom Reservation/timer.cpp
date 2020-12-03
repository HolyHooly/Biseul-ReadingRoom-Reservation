#include "timer.h"
#include "ui_timer.h"

Timer::Timer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);

//    t_count=0;
//    bt1=new QPushButton("Off",this);
//    bt2=new QPushButton("Stop",this);
//    bt3=new QPushButton("Start",this);
//    bt4=new QPushButton("Init",this);
//    tr1=new QTimer(this);
//    connect(tr1,SIGNAL(timeout()),this,SLOT(timerEvent()));
//    connect(bt2,SIGNAL(clicked()),this,SLOT(timerStop()));
//    connect(bt3,SIGNAL(clicked()),this,SLOT(timerStart()));
//    connect(bt4,SIGNAL(clicked()),this,SLOT(timerInit()));

//    QVBoxLayout *s = new QVBoxLayout;
//    s->addWidget(bt1);
//    s->addWidget(bt2);
//    s->addWidget(bt3);
//    s->addWidget(bt4);
//    setLayout(s);

    this->t_init = QTime(0,0,0);
    this->timer = new QTimer();
    this->Init();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(Update()));
    this->timer->start(1000);

    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(this->s);

    setLayout(l);
}

// 사용자의 선택을 받아와서 더해주면 될 듯 하다.

void Timer::Init() {
    this->t_init = this->t_init.addSecs(5 * 60 * 60);
}

void Timer::Add() {
    QTime temp;
    temp = this->t_init.addSecs(3000);
    this->show_time = temp.toString("hh:mm:ss");
}

void Timer::Update() {
    this->t_init = this->t_init.addSecs(-1);
    this->s = new QLabel(this->t_init.toString());
}

void Timer::Minus() {
    QTime temp;
    temp = this->t_init.addSecs(-1);
    this->show_time = temp.toString("hh:mm:ss");
    this->Update();
}


Timer::~Timer()
{
    delete ui;
}

//void Timer::timerEvent()
//{
// t_count++;
// repaint();
//}
//void Timer::timerStop()
//{
// tr1->stop();
//}
//void Timer::timerInit()
//{
// t_count=0;
// bt1->setText("00:00:00");
//}
//void Timer::timerStart()
//{
// tr1->start(1000);
//}

//void Timer::paintEvent(QPaintEvent *)
//{
// QTime t2(0,0,0);
// QTime n;
// n=t2.addSecs(t_count);
// bt1->setText(n.toString());
//}

