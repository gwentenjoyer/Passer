#include "windowopen.h"
#include "ui_windowopen.h"

WindowOpen::WindowOpen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowOpen)
{
    ui->setupUi(this);
}

WindowOpen::~WindowOpen()
{
    delete ui;
}
