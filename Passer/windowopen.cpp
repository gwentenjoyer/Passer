#include "windowopen.h"
#include "ui_windowopen.h"
#include "initdialog.h"
#include <iostream>
#include "datawindow.h"
#include "sqlitedbmanager.h"
#include <QMessageBox>
#include <QCloseEvent>

#include "hash.h"

WindowOpen::WindowOpen(SqliteDBManager *dbIns, InitDialog *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    ui(new Ui::WindowOpen),
    db(dbIns)
{
    ui->setupUi(this);
//    connect(ui->pbCancel, &QPushButton::clicked, parent, &QWidget::show);
//    connect(ui->pbLogin, &QPushButton::clicked, parent, &QWidget::show);
//    connect(this, SIGNAL(QWindow::closeEvent()), qApp, SLOT(quit()));
}

WindowOpen::~WindowOpen()
{
    delete ui;
}

void WindowOpen::on_pbCancel_clicked()
{
//    this->hide();
//    parent->show();

//    ((InitDialog*) parentWidget())->show();
    parentWin->show();
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
//    db->connectToDataBase();
    UserPublicData *user;
//    QVariantList signInInfo;
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
//        signInInfo.append(hashedPassword);


    //    db->connectToDataBase();
//        if(!db->searchForUser(ui->leUsername->text(), ui->lePassword->text())){
//        user = db->searchForUser(signInInfo);
        user = db->searchForUser(userInfo);
//        if(!(user = db->searchForUser(signInInfo))){
//            qDebug() << "Cannot find user with this input data.";
//            QMessageBox *modalWid = new QMessageBox(this);
//            modalWid->setModal(true);
//            modalWid->setText("Cannot find user with this input data.");
//            modalWid->show();
//        }
//        db->insertIntoUsers(TABLE_USERS, signInInfo);
//        else{
            DataWindow *dw = new DataWindow(db, user, this);
            dw->show();
            hide();
//        }
        }
        catch(QString err){
            QMessageBox *modalWid = new QMessageBox(this);
            modalWid->setModal(true);
            modalWid->setText(err);
            modalWid->show();
    }
}

void WindowOpen::closeEvent (QCloseEvent *event)
{
//        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Passer",
//                                                                    tr("Are you sure?\n"),
//                                                                    QMessageBox::No | QMessageBox::Yes,
//                                                                    QMessageBox::Yes);
//        if (resBtn != QMessageBox::Yes) {
//            event->ignore();
//        } else {
//            event->accept();
//            QApplication::quit();
//        }
    event->accept();
    QApplication::quit();
}
