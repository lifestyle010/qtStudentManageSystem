#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include<QMessageBox>
#include<qstring.h>
#include"connection.h"
#include"widget.h"
class Login : public QDialog
{
    Q_OBJECT
public:
    Login();
    ~Login();
public:
    bool myLogin();
    void myAdmin();
    void myQuit();
    void mySet();
protected:
    QLineEdit * userL;
    QLineEdit * passwdL;
    QLineEdit * hostL;
    QLineEdit * databnL;
    QLineEdit * ptL;

    QPushButton *  loginB;
    QPushButton * adminB;
    QPushButton * quitB;
    QPushButton * settingB;
private:
    //connect

};

class Set : public QDialog
{
    Q_OBJECT
public:
    Set();

    ~Set();
public:
    void save();
private:
    QLineEdit * HOST;
    QLineEdit * DB;
    QLineEdit * PORT_;




};

class Admin : public QDialog
{
    Q_OBJECT
public:
    Admin();
    ~Admin();
public:
    void Login();
private:
    QLineEdit * userL;
    QLineEdit * passwdL;
    QPushButton *  loginB;
    QPushButton * quitB;
};

#endif // LOGIN_H
