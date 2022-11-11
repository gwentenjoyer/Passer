#include "initdialog.h"
#include "ui_initdialog.h"

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

