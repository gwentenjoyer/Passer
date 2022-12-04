#include "addentry.h"
#include "ui_addentry.h"
#include <QString>
#include <QVariantList>
#include <QMessageBox>
#include "datawindow.h"

//AddEntry::AddEntry(QWidget *parent) :
AddEntry::AddEntry(SqliteDBManager *db, Users *currUser, QMainWindow *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    db(db),
    currUser(currUser),
    ui(new Ui::AddEntry)
{
    ui->setupUi(this);
//    setWindowModality(Qt::WindowModal);
    setModal(true);
    hide(); show();
//    this->setModal();
}

AddEntry::~AddEntry()
{
//    parentWin->
    delete ui;
}

void AddEntry::on_pbCancel_clicked()
{
    delete this;
}


void AddEntry::on_pbAdd_clicked()
{
    // if()
    QVariantList data;
    try{
        data.append(ui->leTitle->text());
        data.append(ui->leUrl->text());
        data.append(ui->leUsername->text());
        data.append(ui->lePassword->text());
        data.append(ui->leDescription->text());
        db->insertIntoData(TABLE_DATA, currUser, data);

        delete this;
    }
    catch(QString err){
        QMessageBox *modalWid = new QMessageBox(this);
        modalWid->setModal(true);
        modalWid->setText(err);
        modalWid->show();
    }
//    delete thi
}

