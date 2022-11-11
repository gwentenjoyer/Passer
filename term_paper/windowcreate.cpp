#include "windowcreate.h"
#include "ui_windowcreate.h"

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
