#include "editentry.h"
#include "ui_editentry.h"
#include <QDebug>

//EditEntry::EditEntry(QWidget *parent) :
EditEntry::EditEntry(SqliteDBManager *db, const QVariantList &list, QWidget *parent) :
//    QDialog(parent),
    ui(new Ui::EditEntry),
    db(db),
    list(list)
{
    ui->setupUi(this);
    // list[0] is id
    ui->leTitle->setText(list[1].toString());
    ui->leUrl->setText(list[2].toString());
    ui->leUsername->setText(list[3].toString());
    ui->lePassword->setText(list[4].toString());
    ui->leDescription->setText(list[5].toString());
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
    list[1] = ui->leTitle->text();
    list[2] = ui->leUrl->text();
    list[3] = ui->leUsername->text();
    list[4] = ui->lePassword->text();
    list[5] = ui->leDescription->text();
    try{
        db->updateDataRow(list);
        delete this;
    }
    catch(QString err){
        qDebug() << err;
    }
}

