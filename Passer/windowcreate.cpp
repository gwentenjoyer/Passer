#include "windowcreate.h"
#include "ui_windowcreate.h"
#include "initdialog.h"
#include "datawindow.h"
#include <QVariantList>
#include <QMessageBox>

#include "hash.h"
#include "datainfo.h"
#include "userinfo.h"

//WindowCreate::WindowCreate(SqliteDBManager *dbIns, QWidget *parent) :
WindowCreate::WindowCreate(SqliteDBManager *dbIns, InitDialog *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    ui(new Ui::WindowCreate),
    db(dbIns)
{
    ui->setupUi(this);
}

WindowCreate::~WindowCreate()
{
    delete ui;
}

void WindowCreate::on_pbCancel_clicked()
{
//    ((InitDialog*) parentWidget())->show();
    parentWin->show();
    delete this;
}


void WindowCreate::on_pbSignin_clicked()
{
//    QVariantList signInInfo;
    UserPublicData *user;
    QString hashedPassword(getHexHashOfQString(ui->lePassword->text()));
    UserInfo userInfo(ui->leUsername->text(), hashedPassword);
//    if(ui->leUsername->text() == "" || ui->lePassword->text() == ""){
//        qDebug() << "Fields cannot be empty.";
//        QMessageBox *modalWid = new QMessageBox(this);
//        modalWid->setModal(true);
//        modalWid->setText("Fields cannot be empty.");
//        modalWid->show();
//    }
//    else{
        try{


//        hashedPassword = getHexHashOfQString(ui->lePassword->text());
//        qDebug() << hashedPassword;

//        signInInfo.append(ui->leUsername->text());
//        signInInfo.append(ui->lePassword->text());
//        signInInfo.append(hashedPassword);


    //    db->connectToDataBase();
//        db->insertIntoUsers(TABLE_USERS, signInInfo);

        db->insert(userInfo);
        user = db->searchForUser(userInfo);
        DataWindow *dw = new DataWindow(db, user, this);
        dw->show();
        hide();
    }
        catch(QString err){
            QMessageBox *modalWid = new QMessageBox(this);
            modalWid->setModal(true);
            modalWid->setText(err);
            modalWid->show();
//        }
    }
}

void WindowCreate::closeEvent (QCloseEvent *event)
{
    event->accept();
    QApplication::quit();
}
