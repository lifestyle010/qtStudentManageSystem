#include "widget.h"
#include <QApplication>
#include"manage.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login myLogin;
    myLogin.show();
    //Widget * w = new Widget;
    //w->show();
    return a.exec();
}
