#include "windowcreate.h"
#include "ui_windowlogin.h"
#include "initdialog.h"
#include "datawindow.h"
#include <QVariantList>
#include <QMessageBox>

#include "hash.h"
#include "datainfo.h"
#include "userinfo.h"
#include "changepassword.h"

ChangePassword::ChangePassword(InitDialog *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    ui(new Ui::WindowLogin),
    db(SqliteDBManager::getInstance())
{
    ui->setupUi(this);
    ui->checkBox->hide();
    setWindowTitle("Passer - Change password");
    ui->leUsername->setEchoMode(QLineEdit::Password);
    ui->labelUsername->setText("Old password");
    ui->labelPassword->setText("New password");
    ui->pbContinue->setText("Change");
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_pbCancel_clicked()
{
    parentWin->show();
    delete this;
}


void ChangePassword::on_pbContinue_clicked()
//void WindowCreate::on_pbSignin_clicked()
{

}

void ChangePassword::closeEvent (QCloseEvent *event)
{
    event->accept();
    QApplication::quit();
}



