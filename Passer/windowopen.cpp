#include "windowopen.h"
#include "ui_windowopen.h"
#include "initdialog.h"
#include <iostream>
#include "datawindow.h"
#include "sqlitedbmanager.h"

WindowOpen::WindowOpen(SqliteDBManager *dbIns, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowOpen),
    db(dbIns)
{
    ui->setupUi(this);
//    connect(ui->pbCancel, &QPushButton::clicked, parent, &QWidget::show);
//    connect(ui->pbLogin, &QPushButton::clicked, parent, &QWidget::show);
}

WindowOpen::~WindowOpen()
{
    delete ui;
}

void WindowOpen::on_pbCancel_clicked()
{
//    this->hide();
//    parent->show();

    ((InitDialog*) parentWidget())->show();
    delete this;
}


void WindowOpen::on_pbLogin_clicked()
{
//    SqliteDBManager *users = new SqliteDBManager;
//    users->getObject();
//    users->connectToDataBase("mybdor.sqlite", "localhost");
//    SqliteDBManager *users = new SqliteDBManager;
//    users->getInstance();
//    users->connectToDataBase("mybdor.sqlite", "localhost");
    db->connectToDataBase();

    DataWindow *dw = new DataWindow(this);
    dw->show();
    hide();

}

