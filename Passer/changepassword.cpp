#include <QMessageBox>
#include "changepassword.h"
#include "hash.h"
#include "sqlitedbmanager.h"

ChangePassword::ChangePassword(UserPublicData *upi, QWidget *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    currentUser(upi),
    ui(new Ui::WindowLogin),
    db(SqliteDBManager::getInstance())
{
    ui->setupUi(this);
//    ui->checkBox->hide();
    setWindowModality(Qt::WindowModal);
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
    delete this;
}


void ChangePassword::on_pbContinue_clicked()
//void WindowCreate::on_pbSignin_clicked()
{
    try{

        QString oldPassword = getHexHashOfQString(ui->leUsername->text()),
                savedPassword = db->getPasswordHash(currentUser);
//    if(getHexHashOfQString(ui->lePassword->text()) == db->getPasswordHash(currentUser)){
        if (oldPassword == savedPassword){
            db->updatePasswordHash(currentUser, getHexHashOfQString(ui->lePassword->text()));
            delete this;
        }
        else{
            qDebug() << "wrong password";
            throw (QString)"Wrong password for user.";
        }
    }
    catch(QString err){
        QMessageBox *modalWid = new QMessageBox(this);
        modalWid->setModal(true);
        modalWid->setText(err);
        modalWid->show();
    }
}

void ChangePassword::closeEvent (QCloseEvent *event)
{
    event->accept();
}


void ChangePassword::on_checkBox_stateChanged(int state)
{
    if(state){
        ui->lePassword->setEchoMode(QLineEdit::Normal);
        ui->leUsername->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->lePassword->setEchoMode(QLineEdit::Password);
        ui->leUsername->setEchoMode(QLineEdit::Password);
    }
}
