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


//bool InitDialog::choseOption(){
////    if (ui->pbCreate->clicked())
////        return true;
////    else if (ui->pbOpen->clicked())
////        return false;
////    return ui->pbCreate->pressed()? true : false;
//    return optionChosen;
//}

void InitDialog::on_pbOpen_clicked()
{
//    optionChosen = true;
    WindowOpen *winOp = new WindowOpen;
//    WindowOpen winOp;
//    optionChosen = false;
    this->hide();
    winOp->show();
}


void InitDialog::on_pbCreate_clicked()
{
    WindowCreate *winCr = new WindowCreate;
//    WindowCreate winCr;
//    optionChosen = false;
    this->hide();
    winCr->show();
}

