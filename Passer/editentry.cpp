#include "editentry.h"
#include "ui_dataentry.h"
#include <QDebug>
#include "datawindow.h"

EditEntry::EditEntry(const DataInfo &dataInfo, QWidget *parent)
//    QDialog(parent),
    : ui(new Ui::EditEntry)
    , dataInfo(dataInfo)
{

    ui->setupUi(this);
    setWindowTitle("Edit entry...");
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


//void EditEntry::on_pbEdit_clicked()
void EditEntry::on_pbProceed_clicked()
{
    dataInfo.setTitle(ui->leTitle->text());
    dataInfo.setUrl(ui->leUrl->text());
    dataInfo.setUsername(ui->leUsername->text());
    dataInfo.setPassword(ui->lePassword->text());
    dataInfo.setDescription(ui->leDescription->text());
    try{
        SqliteDBManager::getInstance()->updateDataRow(dataInfo);
        delete this;
    }
    catch(QString err){
        qDebug() << err;
    }
}

