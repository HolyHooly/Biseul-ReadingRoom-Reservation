#include "RegisterPanel.h"
#include "ui_RegisterPanel.h"

RegisterPanel::RegisterPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterPanel)
{
    ui->setupUi(this);

    // whole layout
    QVBoxLayout *vlayout = new QVBoxLayout;

    // ����
    label = new QLabel("Appliciant");
    // ���
    brouser = new QTextBrowser();
    QString q = QString(tr("�������� ���� �� �̿� ����""\n"
                           "�� ���α׷� �� ���񽺸� �̿��ϴ� ���, �Ʒ� ���׿� ���� ���� �Ŀ��� �̿� �����մϴ�."
                           "\n"
                           "\n"
                           "1. ���������� �����׸� �� �̿� ����"
                           "\n"
                           "A. �� ���α׷�('�񽽺����� ������ �¼� ���� ���α׷�')�� ������ ���� ���������� �����Ͽ� �̿��մϴ�.""\n"
                           "    �ʼ��׸�: �̸�, �й�, �л��� RFID ����"
                           "\n"
                           "B. ���� �̿�����̳� ��Ȱ���л���ġȸ�� ��� ���� ������ ���� �������� �����Ǿ� ������ �� �ֽ��ϴ�.""\n"
                           "    i. ȸ������ ���, �¼� ����/�ݳ�/�ڸ���� ����""\n"
                           "    ii. ������ �̿� ��Ģ ���ݿ� ���� ����""\n"
                           "\n"
                           "C. �̿����""\n"
                           "    i. ������ �¼� �缮ȭ ����""\n"
                           "        ��) �̿��� ������ ���� �ߺ� ���� �� �¼� �缮ȭ ����"
                           "\n"
                           "\n"
                           "2. ���������� ���� ���"
                           "\n"
                           "\n"
                           "ȸ������ ����� 1ȸ ��������(�̸�, �й�, �л���RFID��ȣ)�� �����˴ϴ�."
                           "\n"
                           "\n"
                           "3. ���������� ���� �� �̿�Ⱓ""\n""\n"
                           "A. �̿����� ���������� �� ���α׷��� ���񽺸� �����ϴ� �Ⱓ ���ȿ� ���� �� �̿�ǰ�, ȸ�� Ż�� �� ������ ������ ������ ���� �Ǵ� �̿�� �� ������ �ı� ó���˴ϴ�. �ٸ�, ��������� ������ ���Ͽ� ������ �ʿ伺�� �ִ� ��쿡�� ������ɿ� ���� �����մϴ�."
                           "\n"
                           "B. �̿����� ���Ǹ� �޾� �����ϰ� �ִ� �̿볻���� ���� �̿��ڰ� ������ �䱸�ϴ� ��쿡�� ��ü ���� �ش� ������ ����/Ȯ�� �� �� �ֵ��� ��ġ�մϴ�."
                           "\n"
                           "C. �̿��ڰ� ���� ����� �����Ͻ� ���Ŀ��� 6������ �ٸ� ������� �缮ȭ ���� �� �������� ��Ȱ�� ��� ���Ͽ� �¼� ��� �α״� �����մϴ�."
                           "\n"
                           "\n"
                           "4. Ż�� �ȳ�"
                           "\n"
                           "A. ȸ�� Ż���� ��� ��� ���װ� �����Ͽ�, Ż��/�簡�� �ǿ� ������ ���� ��Ȱ����ġȸ�� ���� �� Ż��ó�� �����մϴ�."
                           "\n"
                           "\n"
                           "[��Ģ] (������) �� ����� 2019�� 9�� 2�Ϻ��� ���� �մϴ�.));"));
    brouser->setText(q);

    // component 3
    hlayout1 = new QHBoxLayout;
    hlayout2 = new QHBoxLayout;
    hb_con = new QHBoxLayout;
    hh_con = new QVBoxLayout;
    button_con = new QVBoxLayout;

    // �̸�
    QLabel *name_label = new QLabel("�̸�");
    // �й�
    QLabel *bunho_label = new QLabel("�й�");

    // depending on "letter", minimum can be changed
    name_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    bunho_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    name_label->setMinimumWidth(80);
    bunho_label->setMinimumWidth(80);

    input_name = new QLineEdit();
    input_number = new QLineEdit();

    hlayout1->addWidget(name_label);
    hlayout1->addWidget(input_name);

    hlayout2->addWidget(bunho_label);
    hlayout2->addWidget(input_number);

    hh_con->addLayout(hlayout1);
    hh_con->addLayout(hlayout2);

    // Ȯ��, ��� ��ư
    confirm = new QPushButton("register");
    nono = new QPushButton("cancel");
    button_con->addWidget(confirm);
    button_con->addWidget(nono);

    hb_con->addLayout(hh_con);
    hb_con->addLayout(button_con);

    vlayout->addWidget(label);
    vlayout->addWidget(brouser);
    vlayout->addLayout(hb_con);

    // showing layout
    setModal(true);
    setLayout(vlayout);
    setWindowTitle("Applications");

//    mdialog.exec();

    // connect
    connect(nono, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(confirm, SIGNAL(clicked()), this, SLOT(TAG()));
}

RegisterPanel::~RegisterPanel()
{
    delete ui;
}

void RegisterPanel::cancel() {
    this->close();
}

void RegisterPanel::TAG() {
    rf = new RfidPanel;
    rf->show();
    this->close();
}
