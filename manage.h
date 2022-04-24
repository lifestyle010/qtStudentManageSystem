#ifndef MANAGE_H
#define MANAGE_H
#include"login.h"
#include<QSqlTableModel>
#include<QListWidget>
class QSqlTableModel;
class Widget;
class Manage : public QDialog
{
public:
    Manage();
    Manage(const QString &tableName,const QString &primarykey);
    ~Manage();
public:
    QTableView * TableView;
    QSqlTableModel * model;
    QListWidget * ListWidget;
    QLineEdit * queryL;
public:
    void submitS();
    void revertS();
    void addRecordS();
    void deleteLineS();
    void selectS();
    void showAllTableS();
public:
    QString tableName_;
    QString selectName_;
};


#endif // MANAGE_H
