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
    label = new QLabel("Terms of Use");
    // 약관

    std::ifstream in("./data/terms.txt");
    std::string s;
    
    if (in.is_open()) {
        in.seekg(0, std::ios::end);
        int size = in.tellg();
        s.resize(size);
        in.seekg(0, std::ios::beg);
        in.read(&s[0], size);
    }

    QString q = QString::fromStdString(s);
    brouser = new QTextBrowser();
    brouser->setText(q);

    // component 3
    hlayout1 = new QHBoxLayout;
    hlayout2 = new QHBoxLayout;
    hb_con = new QHBoxLayout;
    hh_con = new QVBoxLayout;
    button_con = new QVBoxLayout;

    // 이름
    QLabel *name_label = new QLabel(QString::fromLocal8Bit("이름/Name"));
    // 학번
    QLabel *bunho_label = new QLabel(QString::fromLocal8Bit("학번/Student ID"));

    // depending on "letter", minimum can be changed
    name_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    bunho_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    name_label->setMinimumWidth(80);
    bunho_label->setMinimumWidth(80);

    input_name = new QLineEdit();
    input_number = new QLineEdit();

    QRegularExpression name_rx(QString::fromLocal8Bit("^[A-Za-z가-힣\\s]*$"));
    QRegularExpression id_rx("20\\d{2}(0|1|2|3|4)(0|1|2|3|4)\\d{3}");
    QValidator* name_validator = new QRegularExpressionValidator(name_rx, this);
    QValidator* id_validator = new QRegularExpressionValidator(id_rx, this);
    input_name->setValidator(name_validator);
    input_number->setValidator(id_validator);

    
    input_name->setValidator(name_validator);

    hlayout1->addWidget(name_label);
    hlayout1->addWidget(input_name);

    hlayout2->addWidget(bunho_label);
    hlayout2->addWidget(input_number);

    hh_con->addLayout(hlayout1);
    hh_con->addLayout(hlayout2);

    // 확인, 취소 버튼
    confirm = new QPushButton("Register");
    nono = new QPushButton("Cancel");
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
    setWindowTitle("Sign Up");

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
    RfidPanel rf;
    if (rf.exec() == QDialog::Accepted) {
        rfid_id = rf.getdata();
    }
}
