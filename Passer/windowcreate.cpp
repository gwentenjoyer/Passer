#include "windowcreate.h"
#include "ui_windowlogin.h"
#include "initdialog.h"
#include "datawindow.h"
#include <QVariantList>
#include <QMessageBox>

#include "hash.h"
#include "datainfo.h"
#include "userinfo.h"

WindowCreate::WindowCreate(InitDialog *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    ui(new Ui::WindowLogin),
    db(SqliteDBManager::getInstance())
{
    ui->setupUi(this);
}

WindowCreate::~WindowCreate()
{
    delete ui;
}

void WindowCreate::on_pbCancel_clicked()
{
    parentWin->show();
    delete this;
}


void WindowCreate::on_pbContinue_clicked()
//void WindowCreate::on_pbSignin_clicked()
{
    UserPublicData *user;
    QString hashedPassword(getHexHashOfQString(ui->lePassword->text()));
    UserInfo userInfo(ui->leUsername->text(), hashedPassword);

    try {
        db->insert(userInfo);
        user = db->searchForUser(userInfo);
        DataWindow *dw = new DataWindow(user, this);
        connect(dw, &QWidget::destroyed, this, &on_pbCancel_clicked, Qt::UniqueConnection);
        dw->show();
        ui->lePassword->setText("");
        hide();
    }
    catch(QString err){
        QMessageBox *modalWid = new QMessageBox(this);
        modalWid->setModal(true);
        modalWid->setText(err);
        modalWid->show();
    }
}

void WindowCreate::closeEvent (QCloseEvent *event)
{
    event->accept();
    QApplication::quit();
}


void WindowCreate::on_checkBox_stateChanged(int state)
{
    if(state){
        ui->lePassword->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->lePassword->setEchoMode(QLineEdit::Password);
    }
}


