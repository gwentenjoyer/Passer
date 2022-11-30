#include "windowopen.h"
#include "ui_windowopen.h"
#include "initdialog.h"
#include <iostream>
#include "datawindow.h"
#include "sqlitedbmanager.h"

WindowOpen::WindowOpen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowOpen)
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
    SqliteDBManager *users = new SqliteDBManager;
    users->getObject();
    users->connectToDataBase("mybdor.sqlite", "localhost");
    DataWindow *dw = new DataWindow(this);
    dw->show();
    hide();

}

