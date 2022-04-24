#include "manage.h"
#include"widget.h"
Manage::Manage()
{

}

Manage::Manage(const QString &tableName,const QString &primarykey)
{
    //ui
    QString icon = QString(":/%1.png").arg(tableName);
	setWindowIcon(QIcon(icon)); 
    QString title = QString("%1 manage").arg(tableName);
    setWindowTitle(title);
    this->resize(1000,600);
    QHBoxLayout * HBoxLayout = new QHBoxLayout(this);

    this->tableName_ = tableName;
    this->selectName_ = primarykey;
    //left
    QGroupBox * left = new QGroupBox("数据库资源");
    TableView = new QTableView;
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    TableView->setModel(model);
    QHBoxLayout * AutoHBoxLayout = new QHBoxLayout;
    AutoHBoxLayout->addWidget(TableView);
    left->setLayout(AutoHBoxLayout);
    //connect

    //right
    QGroupBox * right = new QGroupBox("functions");
    QGridLayout * Buttons = new QGridLayout;
    QPushButton * submitB = new QPushButton("提交修改");
    QPushButton * rollbackB = new QPushButton("撤销修改");
    QPushButton * addRecordB = new QPushButton("添加");
    QPushButton * deleteLineB = new QPushButton("删除选中行");
    QPushButton * selectB = new QPushButton("查询");
    QPushButton * showAllTableB = new QPushButton("显示全表");
    submitB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    rollbackB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    addRecordB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    deleteLineB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    selectB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    showAllTableB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    queryL = new QLineEdit();
    QFormLayout * form = new QFormLayout;
    form->addRow(primarykey,queryL);
    Buttons->addWidget(submitB,0,0,1,1);
    Buttons->addWidget(rollbackB,0,1,1,1);
    Buttons->addWidget(addRecordB,1,0,1,1);
    Buttons->addWidget(deleteLineB,1,1,1,1);
    Buttons->addLayout(form,2,0,1,2);
    Buttons->addWidget(selectB,3,0,1,2);
    Buttons->addWidget(showAllTableB,4,0,1,2);
    right->setLayout(Buttons);
    //connect
    QObject::connect(submitB,&QPushButton::clicked,this,&Manage::submitS);
    QObject::connect(rollbackB,&QPushButton::clicked,this,&Manage::revertS);
    QObject::connect(addRecordB,&QPushButton::clicked,this,&Manage::addRecordS);
    QObject::connect(deleteLineB,&QPushButton::clicked,this,&Manage::deleteLineS);
    QObject::connect(selectB,&QPushButton::clicked,this,&Manage::selectS);
    QObject::connect(showAllTableB,&QPushButton::clicked,this,&Manage::showAllTableS);
    HBoxLayout->addWidget(left,4);
    HBoxLayout->addWidget(right,2);

}

void Manage::submitS()
{
    model->database().transaction();
    if(model->submitAll())
        model->database().commit();
    else
    {
        model->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),tr("数据库错误：%1").arg(model->lastError().text()));
    }
}

void Manage::revertS()
{
    model->revert();
}

void Manage::addRecordS()
{
    int rowNum = model->rowCount();
    model->insertRow(rowNum);
}

void Manage::deleteLineS()
{
    int curRow = this->TableView->currentIndex().row();
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行！"),tr("确定删除？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        model->revertAll();
    }
    else
    {
        model->submitAll();
    }
}

void Manage::selectS()
{
    QString queryT = queryL->text();
    if(queryT.length())
    {
        model->setFilter(QString("%1 = '%2'").arg(selectName_).arg(queryT));
        model->select();
    }
    else
    {
        QMessageBox::warning(this,tr("warning"),tr("查询项不能为空"));
    }
}

void Manage::showAllTableS()
{
    model->setTable(tableName_);
    model->select();

}

Manage::~Manage()
{

}
