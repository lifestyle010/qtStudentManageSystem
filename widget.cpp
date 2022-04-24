#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowIcon(QIcon(":/homepage.png"));
    setWindowTitle("学生信息管理系统");
    this->resize(1000,600);
    QPushButton * classB,* stuB,* subjectB,* courseB,* scoreB,* logoutB;
    classB = new QPushButton("班级管理");
    stuB = new QPushButton("学生管理");
    subjectB = new QPushButton("科目管理");
    courseB = new QPushButton("课程管理");
    scoreB = new QPushButton("成绩管理");
    logoutB = new QPushButton("注销");
    classB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    stuB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    subjectB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    courseB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scoreB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    logoutB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QGridLayout * GLayout = new QGridLayout;
    GLayout->setVerticalSpacing(0);
    GLayout->setHorizontalSpacing(0);
    GLayout->addWidget(classB,0,0,1,1);
    GLayout->addWidget(stuB,0,1,1,1);
    GLayout->addWidget(subjectB,0,2,1,1);
    GLayout->addWidget(courseB,1,0,1,1);
    GLayout->addWidget(scoreB,1,1,1,1);
    GLayout->addWidget(logoutB,1,2,1,1);
    this->setLayout(GLayout);

    QObject::connect(classB,&QPushButton::clicked,this,&Widget::MyClass);
    QObject::connect(stuB,&QPushButton::clicked,this,&Widget::MyStu);
    QObject::connect(subjectB,&QPushButton::clicked,this,&Widget::MySubject);
    QObject::connect(courseB,&QPushButton::clicked,this,&Widget::MyCourse);
    QObject::connect(scoreB,&QPushButton::clicked,this,&Widget::MyScore);
    QObject::connect(logoutB,&QPushButton::clicked,this,&Widget::logoutS);

}

Widget::~Widget()
{

}

void Widget::MyClass()
{
    M = new Manage("class","班主任");//selectName填写查询key
    M->show();
}

void Widget::MyStu()
{
    M = new Manage("student","姓名");
    M->show();
}
void Widget::MySubject()
{
    M = new Manage("subject","科目名");
    M->show();
}
void Widget::MyCourse()
{
    M = new Manage("course","授课老师");
    M->show();
}
void Widget::MyScore()
{
    M = new Manage("score","学生姓名");
    M->show();
}

void Widget::logoutS()
{
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString workindDirectory = QDir::currentPath();
    QProcess::startDetached(program,arguments,workindDirectory);
    QApplication::exit();

}
