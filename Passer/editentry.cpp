#include "editentry.h"
#include "ui_editentry.h"
#include <QDebug>
#include "datawindow.h"

//EditEntry::EditEntry(QWidget *parent) :
//EditEntry::EditEntry(SqliteDBManager *db, const QVariantList &list, QWidget *parent) :
EditEntry::EditEntry(SqliteDBManager *db, const DataInfo &dataInfo, QWidget *parent) :
//    QDialog(parent),
    ui(new Ui::EditEntry),
    db(db),
//    list(list)
    dataInfo(dataInfo)
{

    ui->setupUi(this);

//    connect(this, &closeEvent, parent, &DataWindow::on_pbRefresh_clicked);
    // list[0] is id
//    ui->leTitle->setText(list[1].toString());
//    ui->leUrl->setText(list[2].toString());
//    ui->leUsername->setText(list[3].toString());
//    ui->lePassword->setText(list[4].toString());
//    ui->leDescription->setText(list[5].toString());

    ui->leTitle->setText(dataInfo.getTitle());
    ui->leUrl->setText(dataInfo.getUrl());
    ui->leUsername->setText(dataInfo.getUsername());
    ui->lePassword->setText(dataInfo.getPassword());
    ui->leDescription->setText(dataInfo.getDescription());
}

EditEntry::~EditEntry()
{
    delete ui;
}

void EditEntry::on_pbCancel_clicked()
{
    delete this;
}


void EditEntry::on_pbEdit_clicked()
{
//    list[1] = ui->leTitle->text();
//    list[2] = ui->leUrl->text();
//    list[3] = ui->leUsername->text();
//    list[4] = ui->lePassword->text();
//    list[5] = ui->leDescription->text();
    dataInfo.setTitle(ui->leTitle->text());
    dataInfo.setUrl(ui->leUrl->text());
    dataInfo.setUsername(ui->leUsername->text());
    dataInfo.setPassword(ui->lePassword->text());
    dataInfo.setDescription(ui->leDescription->text());
    try{
        db->updateDataRow(dataInfo);
        delete this;
    }
    catch(QString err){
        qDebug() << err;
    }
}

