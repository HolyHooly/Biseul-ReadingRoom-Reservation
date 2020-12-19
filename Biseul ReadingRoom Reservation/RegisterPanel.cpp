///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 29. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////
#include "RegisterPanel.h"
#include "ui_RegisterPanel.h"

RegisterPanel::RegisterPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterPanel)
{
    ui->setupUi(this);

    // whole layout
    QVBoxLayout *vlayout = new QVBoxLayout;
    setStyleSheet({ "background-color:rgb(255,255,255);" });
    setWindowIcon(QIcon("./assets/icon.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

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
    browser = new QTextBrowser();
    browser->setText(q);

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
    confirm_btn = new QPushButton("Register");
    cancel_btn = new QPushButton("Cancel");
    button_con->addWidget(confirm_btn);
    button_con->addWidget(cancel_btn);

    hb_con->addLayout(hh_con);
    hb_con->addLayout(button_con);

    vlayout->addWidget(label);
    vlayout->addWidget(browser);
    vlayout->addLayout(hb_con);

    // showing layout
    setModal(true);
    setLayout(vlayout);
    setWindowTitle("Sign Up");

//    mdialog.exec();

    // connect
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(confirm_btn, SIGNAL(clicked()), this, SLOT(confirm()));
}

RegisterPanel::~RegisterPanel()
{
    delete label;
    delete browser;
    delete hlayout1;
    delete hlayout2;
    delete hb_con;
    delete hh_con;
    delete button_con;
    delete input_name;
    delete input_number;
    delete confirm_btn;
    delete cancel_btn;
    delete ui;
}

std::string RegisterPanel::get_name()
{
    return name;
}

int RegisterPanel::get_stud_id()
{
    
    QString stud = input_number->text();
    int stud_int = stud.toInt();
    return stud_int;
    
}

void RegisterPanel::cancel() {
    this->close();
}

void RegisterPanel::confirm() {
    
    if (input_name->text().isEmpty()  || input_number->text().isEmpty()) {
        QMessageBox msg;
        msg.setText(QString::fromLocal8Bit("제대로 작성하세요. Please fill appropriately"));
        msg.exec();
    }
    else {
        RfidPanel rf;
        if (rf.exec() == QDialog::Accepted) {
            rfid_id = rf.getdata();
        }
        name = input_name->text().toLocal8Bit(); //8bit for korean data
        stud_id = input_number->text().toInt();
        
        this->accept();

    }
}
