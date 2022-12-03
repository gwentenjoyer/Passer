#include "windowcreate.h"
#include "ui_windowcreate.h"
#include "initdialog.h"

WindowCreate::WindowCreate(SqliteDBManager *dbIns, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCreate),
    db(dbIns)
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

