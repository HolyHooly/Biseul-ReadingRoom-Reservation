#include "RegisterPanel.h"
#include "ui_RegisterPanel.h"

RegisterPanel::RegisterPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterPanel)
{
    ui->setupUi(this);

    // whole layout
    QVBoxLayout *vlayout = new QVBoxLayout;

    // 제목
    label = new QLabel("Appliciant");
    // 약관
    brouser = new QTextBrowser();
    QString q = QString(tr("개인정보 수집 및 이용 동의""\n"
                           "이 프로그램 및 서비스를 이용하는 경우, 아래 사항에 대해 동의 후에만 이용 가능합니다."
                           "\n"
                           "\n"
                           "1. 개인정보의 수집항목 및 이용 목적"
                           "\n"
                           "A. 본 프로그램('비슬빌리지 독서실 좌석 예약 프로그램')은 다음과 같이 개인정보를 수집하여 이용합니다.""\n"
                           "    필수항목: 이름, 학번, 학생증 RFID 정보"
                           "\n"
                           "B. 서비스 이용과정이나 생활관학생자치회의 운영에 따라 다음과 같은 정보들이 생성되어 수집될 수 있습니다.""\n"
                           "    i. 회원가입 기록, 좌석 예약/반납/자리비움 내역""\n"
                           "    ii. 독서실 이용 규칙 위반에 관한 내역""\n"
                           "\n"
                           "C. 이용목적""\n"
                           "    i. 독서실 좌석 사석화 방지""\n"
                           "        가) 이용자 관리를 통한 중복 예약 및 좌석 사석화 방지"
                           "\n"
                           "\n"
                           "2. 개인정보의 수집 방법"
                           "\n"
                           "\n"
                           "회원가입 진행시 1회 개인정보(이름, 학번, 학생증RFID번호)가 수집됩니다."
                           "\n"
                           "\n"
                           "3. 개인정보의 보유 및 이용기간""\n""\n"
                           "A. 이용자의 개인정보는 본 프로그램의 서비스를 제공하는 기간 동안에 보유 및 이용되고, 회원 탈퇴 시 수집된 개인의 정보가 열람 또는 이용될 수 없도록 파기 처리됩니다. 다만, 관계법령의 규정에 의하여 보존할 필요성이 있는 경우에는 관계법령에 따라 보존합니다."
                           "\n"
                           "B. 이용자의 동의를 받아 보유하고 있는 이용내역에 대해 이용자가 열람을 요구하는 경우에는 지체 없이 해당 정보를 열람/확인 할 수 있도록 조치합니다."
                           "\n"
                           "C. 이용자가 서비스 사용을 종료하신 이후에도 6개월간 다른 사용자의 사석화 방지 및 독서실의 원활한 운영을 위하여 좌석 사용 로그는 보관합니다."
                           "\n"
                           "\n"
                           "4. 탈퇴 안내"
                           "\n"
                           "A. 회원 탈퇴의 경우 경고 사항과 관련하여, 탈퇴/재가입 악용 방지를 위해 생활관자치회로 연락 후 탈퇴처리 가능합니다."
                           "\n"
                           "\n"
                           "[부칙] (시행일) 본 약관은 2019년 9월 2일부터 시행 합니다.));"));
    brouser->setText(q);

    // component 3
    hlayout1 = new QHBoxLayout;
    hlayout2 = new QHBoxLayout;
    hb_con = new QHBoxLayout;
    hh_con = new QVBoxLayout;
    button_con = new QVBoxLayout;

    // 이름
    QLabel *name_label = new QLabel("이름");
    // 학번
    QLabel *bunho_label = new QLabel("학번");

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

    // 확인, 취소 버튼
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
