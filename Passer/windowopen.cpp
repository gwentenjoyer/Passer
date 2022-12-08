#include "windowopen.h"
#include "ui_windowlogin.h"

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
    ui(new Ui::WindowLogin),
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
        ui->lePassword->setText("");
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

void WindowOpen::on_checkBox_stateChanged(int state)
{
    if(state){
        ui->lePassword->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->lePassword->setEchoMode(QLineEdit::Password);
    }
}

