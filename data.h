#ifndef DATA_H
#define DATA_H
#include<qstring.h>
class Data
{
public:
    //用户的账号密码
    static QString USERNAME;
    static QString PASSWORD;


    static QString HOSTADDR;
    static QString DATABASENAME;
    static QString PORT;

    //管理员
    static QString RootName;
    static QString RootPasswd;
};

#endif // DATA_H
