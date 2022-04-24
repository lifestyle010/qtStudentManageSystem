#ifndef CONNECTION_H
#define CONNECTION_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<qstring.h>
#include"data.h"
static bool createConnection(QSqlDatabase db)
{
   db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName(Data::HOSTADDR);
   db.setPort(Data::PORT.toInt());
   db.setDatabaseName(Data::DATABASENAME);
   db.setUserName("");
   db.setPassword("");
   if(!db.open())
   {
       return false;
   }
   return true;
}


#endif // CONNECTION_H
