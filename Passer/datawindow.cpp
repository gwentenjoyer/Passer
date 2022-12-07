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

DataWindow::DataWindow(UserPublicData *currUser, QMainWindow *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    ui(new Ui::DataWindow),
    currentUser(currUser),
    db(SqliteDBManager::getInstance()),
    sqlModel(nullptr),
    tableSelectedRowDataId(0)
{
    ui->setupUi(this);
    connect(ui->pbQuit, &QPushButton::clicked, this, &QApplication::quit);
    setWindowTitle("Passer @" + currentUser->username + " - data");
    ui->statusbar->showMessage("Logged as: " + currentUser->username);

    updateTableViewModel(ui->tableView);
    ui->tableView->hideColumn(0);

}

DataWindow::~DataWindow()
{
    delete currentUser;
    delete sqlModel;
    delete ui;
}

void DataWindow::on_pbQuit_clicked()
{

}


void DataWindow::on_pbAdd_clicked()
{
    AddEntry *addRow = new AddEntry(currentUser, this);
    addRow->show();
    updateTableViewModel(ui->tableView);
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

QSqlQueryModel* DataWindow::getQueryModel() {
QSqlQueryModel *sqlmodel = new QSqlQueryModel(this);        // possible memory leak

    sqlmodel->setQuery("SELECT "
                   TABLE_DATA ".id, "
                   TABLE_DATA_TITLE ", "
                   TABLE_DATA "." TABLE_DATA_URL ", "
                   TABLE_DATA "." TABLE_DATA_USERNAME ", "
                   TABLE_DATA "." TABLE_DATA_PASSWORD ", "
                   TABLE_DATA "." TABLE_DATA_DESCRIPTION
                   " FROM " TABLE_DATA " INNER JOIN " TABLE_USERS
                   " ON (" TABLE_USERS".id = " TABLE_DATA ".account_id) WHERE "
                   TABLE_DATA ".account_id = " + QString::number(currentUser->id) + ";");
    return sqlmodel;
}

void DataWindow::updateTableViewModel(QTableView *tb) {
    if (sqlModel){
        delete sqlModel;
    }
    sqlModel = getQueryModel();
    tb->setModel(sqlModel);
}

void DataWindow::on_pbRefresh_clicked()
{
    updateTableViewModel(ui->tableView);
}

void DataWindow::on_pbDelete_clicked()
{
    db->deleteDataRow(tableSelectedRowDataId);
    updateTableViewModel(ui->tableView);
}

void DataWindow::on_tableView_clicked(const QModelIndex &index)
{
    tableSelectedRowDataId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
    selectedRow = index.row();
}

void DataWindow::on_pbEdit_clicked()
{
    if(ui->tableView->currentIndex().isValid()){
        EditEntry *editWin = new EditEntry(getInfoFromDataSelectedRow(ui->tableView), this);
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
