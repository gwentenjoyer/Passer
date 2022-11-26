#include "windowcreate.h"
#include "ui_windowcreate.h"
#include "initdialog.h"

WindowCreate::WindowCreate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCreate)
{
    ui->setupUi(this);
}

WindowCreate::~WindowCreate()
{
    delete ui;
}

void WindowCreate::on_pbCancel_clicked()
{
    ((InitDialog*) parentWidget())->show();
    delete this;
}

