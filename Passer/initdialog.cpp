#include "initdialog.h"
#include "ui_initdialog.h"
#include "windowcreate.h"
#include "windowopen.h"

InitDialog::InitDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InitDialog)
{
    ui->setupUi(this);
    connect(ui->pbExit, &QPushButton::clicked, this, &QApplication::quit);
}

InitDialog::~InitDialog()
{
    delete ui;
}

void InitDialog::on_pbOpen_clicked()
{
    WindowOpen *winOp = new WindowOpen(this);
    winOp->show();
    this->hide();
}


void InitDialog::on_pbCreate_clicked()
{
    WindowCreate *winCr = new WindowCreate(this);
    winCr->show();
    this->hide();
}

