#include "initdialog.h"
#include "ui_initdialog.h"
#include "windowcreate.h"
#include "windowopen.h"


InitDialog::InitDialog(SqliteDBManager *dbIns, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InitDialog)
    , db(dbIns)
//    , wCreate(nullptr)
//    , wOpen(nullptr)
{
    ui->setupUi(this);
    connect(ui->pbExit, &QPushButton::clicked, this, &QApplication::quit);
//    QObject::connect( qApp, SIGNAL(destroyed(InitDialog*)), qApp, SLOT(quit()) );
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
//    WindowOpen *winOp = new WindowOpen(this->db);
    WindowOpen *winOp = new WindowOpen(this->db, this);
//    WindowOpen winOp;
//    optionChosen = false;

    winOp->show();
    this->hide();
//    this->setVisible(false);
}


void InitDialog::on_pbCreate_clicked()
{
    WindowCreate *winCr = new WindowCreate(this->db, this);
//    WindowCreate winCr;
//    optionChosen = false;
    winCr->show();
    this->hide();
}

