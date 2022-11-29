#include "addentry.h"
#include "ui_addentry.h"

AddEntry::AddEntry(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddEntry)
{
    ui->setupUi(this);
//    this->setModal();
}

AddEntry::~AddEntry()
{
    delete ui;
}

void AddEntry::on_pbCancel_clicked()
{
    delete this;
}

