#include "windowopen.h"
//#include "ui_windowopen.h"
#include "ui_windowcreate.h"

#include "initdialog.h"
#include <iostream>
#include "datawindow.h"
#include "sqlitedbmanager.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QPushButton>
#include "hash.h"

WindowOpen::WindowOpen(InitDialog *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    ui(new Ui::WindowCreate),
    db(SqliteDBManager::getInstance())
{
    ui->setupUi(this);
    setWindowTitle("Passer - Log into existing account...");
    ui->pbContinue->setText("Log in");
}

WindowOpen::~WindowOpen()
{
    delete ui;
}

void WindowOpen::on_pbCancel_clicked()
{
    parentWin->show();
    delete this;
}

void WindowOpen::on_pbContinue_clicked()
{
    UserPublicData *user;
    QString hashedPassword(getHexHashOfQString(ui->lePassword->text()));
    UserInfo userInfo(ui->leUsername->text(), hashedPassword);

    try {
        user = db->searchForUser(userInfo);

        DataWindow *dw = new DataWindow(user, this);
        dw->show();
        hide();
        }
     catch(QString err) {
        QMessageBox *modalWid = new QMessageBox(this);
        modalWid->setModal(true);
        modalWid->setText(err);
        modalWid->show();
        }
}

void WindowOpen::closeEvent (QCloseEvent *event)
{
    event->accept();
    QApplication::quit();
}
