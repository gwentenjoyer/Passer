#include "datawindow.h"
#include "ui_datawindow.h"
#include <QPushButton>
#include <iostream>
#include "sqlitedbmanager.h"
#include <QSqlTableModel>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>
#include <QSqlQueryModel>
#include "addentry.h"
#include "editentry.h"
#include "datainfo.h"
#include "passerclipboard.h"
#include "changepassword.h"
//QClipboard *cp = QApplication::clipboard();
//QClipboard *cp = qApp->clipboard();

DataWindow::DataWindow(UserPublicData *currUser, QMainWindow *parent)
//    QMainWindow(parent),
    : parentWin(parent)
    , ui(new Ui::DataWindow)
    , currentUser(currUser)
    , db(SqliteDBManager::getInstance())
    , sqlModel(nullptr)
    , tableSelectedRowDataId(0)
    , menu(QMenu(this))
    , act(QAction("Copy", this))
{
    ui->setupUi(this);
    connect(ui->pbQuit, &QPushButton::clicked, this, &QApplication::quit);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(&act,SIGNAL(triggered()), this, SLOT(copySlot()));
    connect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)),SLOT(customContextMenuProceed(QPoint)));
    setWindowTitle("Passer @" + currentUser->username + " - data");
    ui->statusbar->showMessage("Logged as: " + currentUser->username);

    updateTableViewModel(ui->tableView);
    ui->tableView->hideColumn(0);

    ui->tableView->setMouseTracking(true);
//    ui->tableView->viewport()->setAttribute(Qt::WA_Hover,true);
}

void DataWindow::customContextMenuProceed(QPoint pos){
    menu.addAction(&this->act);
    if (selectedCell.x() != 4 && selectedCell.x()!= 3)
        menu.actions().first()->setDisabled(true);
    else
        menu.actions().first()->resetEnabled();
    menu.popup(QCursor::pos());
}
void DataWindow::copySlot(){
    clipboard->clear();
    if(selectedCell.x() == 3){
        ui->statusbar->showMessage("Copied username");
    }
    else if(selectedCell.x() == 4){
        ui->statusbar->showMessage("Copied password");
    }
    clipboard->setText(ui->tableView->model()->index(selectedCell.y(), selectedCell.x()).data().toString());
}

DataWindow::~DataWindow()
{
    delete currentUser;
    delete sqlModel;
    delete ui;
}

void DataWindow::on_pbQuit_clicked() {}

void DataWindow::on_pbAdd_clicked()
{
    AddEntry *addRow = new AddEntry(currentUser, this);
    connect(addRow, &QWidget::destroyed, this, &tableRefresh, Qt::UniqueConnection);
    addRow->show();
}


void DataWindow::on_pbCancel_clicked()
{
    parentWin->show();
    delete this;
}

void DataWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Passer",
                                                                tr("Are you sure you want to exit Passer?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        QApplication::quit();
    }
}



void DataWindow::updateTableViewModel(QTableView *tb) {
    if (sqlModel){
        delete sqlModel;
    }
    sqlModel = db->getQueryModel(currentUser, this);
//    tb->item(0,2)->se
//    QStyleOptionViewItem *opt = tb;
//    initStyleOption(&opt, index);
//    opt.widget->style()->drawItemText(painter, opt.rect, Qt::AlignLeft, opt.palette, true, "*****");
//    Qt::UserRole
//    tb->setModel(sqlModel);
//    QAbstractItemModel *model = sqlModel;
//    qDebug() << sqlModel->rowCount();
//    for(int i = 0; i < sqlModel->rowCount(); ++i){
////            model->index(selectedRow, 0).data().toInt();
////            model->setData(model->index(i, 4), "********");
////            model->index(4, i).data().setValue("****");
////        qDebug() << sqlModel->index(4, i).data().setValue("****");
//        QVariant var("**");
//        qDebug() << var;
////        qDebug() << sqlModel->setData(sqlModel->index(i, 4), var,Qt::UserRole);
//        qDebug() << sqlModel->setData(sqlModel->index(i, 4), var);
//    }
    tb->setModel(sqlModel);
}

void DataWindow::tableRefresh()
{
    updateTableViewModel(ui->tableView);
    ui->statusbar->showMessage("Refreshed");
}

void DataWindow::on_pbDelete_clicked()
{
    db->remove(tableSelectedRowDataId);
    updateTableViewModel(ui->tableView);
    ui->statusbar->showMessage("Deleted");
}

void DataWindow::on_tableView_clicked(const QModelIndex &index)
{
    tableSelectedRowDataId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
    selectedRow = index.row();
    selectedCell.setX(index.column());
    selectedCell.setY(index.row());
}

void DataWindow::on_pbEdit_clicked()
{
    if(ui->tableView->currentIndex().isValid()){
        EditEntry *editWin = new EditEntry(getInfoFromDataSelectedRow(ui->tableView), this);
        connect(editWin, &QWidget::destroyed, this, &tableRefresh, Qt::UniqueConnection);
        editWin->show();
    }
}

DataInfo DataWindow::getInfoFromDataSelectedRow(QTableView *table){
    QAbstractItemModel *model = table->model();
    DataInfo data(model->index(selectedRow, 0).data().toInt(),
                  model->index(selectedRow, 1).data().toString(),
                  model->index(selectedRow, 2).data().toString(),
                  model->index(selectedRow, 3).data().toString(),
                  model->index(selectedRow, 4).data().toString(),
                  model->index(selectedRow, 5).data().toString());

    return data;
}


void DataWindow::on_pbDeleteUser_clicked()
{
//    qDebug() <<
    QMessageBox::StandardButton resBtn =
                                        QMessageBox::question( this, "Passer",
                                        tr("Are you sure you want to delete account?\n"),
                                        QMessageBox::No | QMessageBox::Yes,
                                        QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        db->remove(currentUser);
        on_pbCancel_clicked();
    }
}


void DataWindow::on_pbChangePassword_clicked()
{
    ChangePassword *changeWin = new ChangePassword(currentUser, this);
    changeWin->setWindowModality(Qt::WindowModality::WindowModal);
    changeWin->show();
}

