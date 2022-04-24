#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QListWidget>
#include<QTableWidget>
#include<QGroupBox>
#include<QPushButton>
#include<QLineEdit>
#include"login.h"
#include"manage.h"
#include<QApplication>
#include<qprocess.h>
#include<QDir>
class Manage;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public:
    void MyClass();
    void MyStu();
    void MySubject();
    void MyCourse();
    void MyScore();
    void logoutS();
private:
    Manage * M;
};

#endif // WIDGET_H
