#include "windowopen.h"
#include "ui_windowopen.h"
#include "initdialog.h"
#include <iostream>
#define QT_FATAL_WARNINGS
WindowOpen::WindowOpen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowOpen)
{
    ui->setupUi(this);
//    connect(ui->pbCancel, &QPushButton::clicked, parent, &QWidget::show);
}

WindowOpen::~WindowOpen()
{
    delete ui;
}

void WindowOpen::on_pbCancel_clicked()
{
//    this->hide();
//    parent->show();

    ((InitDialog*) parentWidget())->show();
    delete this;
}

