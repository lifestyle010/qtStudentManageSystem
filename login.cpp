#include"login.h"

Login::Login()
{
    setWindowIcon(QIcon(":/login.png"));
    setWindowTitle("登录");

    QVBoxLayout * VBox = new QVBoxLayout;
    QFormLayout * FormLayout = new QFormLayout;
    userL = new QLineEdit();
    passwdL = new QLineEdit();
    passwdL->setEchoMode(QLineEdit::Password);

    FormLayout->addRow("user:",userL);
    FormLayout->addRow("passwd:",passwdL);
    FormLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);

    QHBoxLayout * HBox = new QHBoxLayout;
    loginB = new QPushButton("登录");
    adminB = new QPushButton("管理员");
    settingB = new QPushButton("设置");
    quitB = new QPushButton("退出");
    HBox->addWidget(loginB);
    HBox->addWidget(adminB);
    HBox->addWidget(settingB);
    HBox->addWidget(quitB);

    VBox->addLayout(FormLayout,2);
    VBox->addLayout(HBox,1);
    this->setLayout(VBox);
    QObject::connect(settingB,&QPushButton::clicked,this,&Login::mySet);
    QObject::connect(loginB,&QPushButton::clicked,this,&Login::myLogin);
    QObject::connect(adminB,&QPushButton::clicked,this,&Login::myAdmin);
    QObject::connect(quitB,&QPushButton::clicked,this,&Login::myQuit);
}

bool Login::myLogin()

{
    //建立连接供验证用
    QSqlDatabase db;
    if(!createConnection(db))
    {
        return false;
    }
    else
    {
        //本地账号密码
        QString _username = userL->text();
        QString _passwd = passwdL->text();
        Data::USERNAME = _username;
        Data::PASSWORD = _passwd;
        QSqlQuery query(db);
        QString queryString = QString("select * from user where username = \"%1\" && passwd = \"%2\";").arg(Data::USERNAME).arg(Data::PASSWORD);
        if(query.exec(queryString))
        {
            query.next();
            if(query.value(2).toInt()==1)
            {
                this->close();
                //连接成功，加入主界面，方法？？？信号还是创建mWidget类并显示
                Widget * w = new Widget;
                w->show();
                return true;
            }
            else if(query.value(2).toInt()!=1)
            {
                QMessageBox::StandardButton result;
                result = QMessageBox::warning(this,"error","账号未启用，请联系管理员处理！",QMessageBox::Yes);
                return false;
            }
        }
        else
        {
           QMessageBox::StandardButton conError;
           conError = QMessageBox::warning(this,"error","账号或密码错误",QMessageBox::Yes);
           return false;
        }
    }
    return false;

}

void Login::myAdmin()
{
    Admin * AdminDia = new Admin;
    AdminDia->exec();
}

void Login::mySet()
{
    Set * SetDia = new Set;
    SetDia->exec();
}

void Login::myQuit()
{
    this->close();
}

Login::~Login()
{

}


Set::Set()
{
    setWindowIcon(QIcon(":/setting.png"));
    setWindowTitle("设置");

    QVBoxLayout * Vbox = new QVBoxLayout;
    QFormLayout * FormLayout = new QFormLayout;

    HOST = new QLineEdit(Data::HOSTADDR);
    DB= new QLineEdit(Data::DATABASENAME);
    PORT_ = new QLineEdit(Data::PORT);
    FormLayout->addRow("hostname:",HOST);
    FormLayout->addRow("DB:",DB);
    FormLayout->addRow("Port:",PORT_);

    QHBoxLayout * HBox = new QHBoxLayout;
    QPushButton * yes = new QPushButton("确认");
    QPushButton * cancel = new QPushButton("取消");

    HBox->addWidget(yes);
    HBox->addWidget(cancel);

    Vbox->addLayout(FormLayout,3);
    Vbox->addLayout(HBox,1);
    setLayout(Vbox);

    QObject::connect(yes,&QPushButton::clicked,this,&Set::save);
    QObject::connect(cancel,&QPushButton::clicked,this,&Set::close);

}
Set::~Set()
{

}

void Set::save()
{
    Data::HOSTADDR = HOST->text();
    Data::DATABASENAME = DB->text();
    Data::PORT = PORT_->text();
    this->close();
}

Admin::Admin()
{
    setWindowIcon(QIcon(":/admin.png"));
    setWindowTitle("Admin");
    QVBoxLayout * VBox = new QVBoxLayout;
    QFormLayout * FormLayout = new QFormLayout;
    userL = new QLineEdit();
    passwdL = new QLineEdit();
    passwdL->setEchoMode(QLineEdit::Password);

    FormLayout->addRow("user:",userL);
    FormLayout->addRow("passwd:",passwdL);
    FormLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);

    QHBoxLayout * HBox = new QHBoxLayout;
    loginB = new QPushButton("登录");
    quitB = new QPushButton("返回");
    HBox->addWidget(loginB);
    HBox->addWidget(quitB);

    VBox->addLayout(FormLayout,2);
    VBox->addLayout(HBox,1);
    this->setLayout(VBox);

    QObject::connect(loginB,&QPushButton::clicked,this,&Admin::Login);
    QObject::connect(quitB,&QPushButton::clicked,this,&Admin::close);//返回不能直接关闭，这个窗口，考虑两个登录的切换，哪个显示另一个隐藏，进入后都关闭，通过注销按钮返回登录界面
}

void Admin::Login()
{
    if(userL->text() == Data::RootName && passwdL->text() == Data::RootPasswd)
    {
        //进入管理员界面
        //测试
        this->close();
        QSqlDatabase db;
        createConnection(db);
        Manage * m = new Manage("user","username");
        m->show();

    }
    else
    {
        QMessageBox::StandardButton conError;
        conError = QMessageBox::warning(this,"error","账号或密码错误",QMessageBox::Yes);
    }
}

Admin::~Admin()
{

}
