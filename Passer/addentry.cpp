#include "addentry.h"
#include "ui_dataentry.h"
#include <QString>
#include <QVariantList>
#include <QMessageBox>
#include "datawindow.h"

#include "datainfo.h"
#include "sqlitedbmanager.h"

AddEntry::AddEntry(UserPublicData *currUser, QMainWindow *parent)
//    QMainWindow(parent)
    : parentWin(parent)
    , currUser(currUser)
    , ui(new Ui::EditEntry)
{
    ui->setupUi(this);
    setWindowTitle("Add new entry...");
    ui->pbProceed->setText("Add");
    setModal(true);
//    hide(); show();
}

AddEntry::~AddEntry()
{
    delete ui;
}

void AddEntry::on_pbCancel_clicked()
{
    delete this;
}

//void AddEntry::on_pbAdd_clicked()
void AddEntry::on_pbProceed_clicked()
{
    DataInfo data(currUser->id,
            ui->leTitle->text(),
            ui->leUrl->text(),
            ui->leUsername->text(),
            ui->lePassword->text(),
            ui->leDescription->text());
    try{
        SqliteDBManager::getInstance()->insert(currUser, data);
        delete this;
    }
    catch(QString err){
        QMessageBox *modalWid = new QMessageBox(this);
        modalWid->setModal(true);
        modalWid->setText(err);
        modalWid->show();
    }
}

