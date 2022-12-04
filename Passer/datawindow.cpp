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

//DataWindow::DataWindow(SqliteDBManager *dbIns, Users *currUser, QWidget *parent) :
DataWindow::DataWindow(SqliteDBManager *dbIns, Users *currUser, QMainWindow *parent) :
//    QMainWindow(parent),
    parentWin(parent),
    ui(new Ui::DataWindow),
    currentUser(currUser),
    db(dbIns),
    sqlModel(nullptr)
{
    ui->setupUi(this);
    connect(ui->pbQuit, &QPushButton::clicked, this, &QApplication::quit);
    setWindowTitle("Passer @" + currentUser->username + " - data");
    ui->statusbar->showMessage("Logged as: " + currentUser->username);

//    QSqlTableModel *model = new QSqlTableModel(this, this->db->getDB());

//    sqlModel = new QSqlQueryModel(this);
//    model->setFilter("account_id = " + currentUser->id);
//    sqlmodel->setQuery("SELECT " TABLE_DATA_TITLE ", "
//                       TABLE_DATA "." TABLE_DATA_URL ", "
//                       TABLE_DATA "." TABLE_DATA_USERNAME ", "
//                       TABLE_DATA "." TABLE_DATA_PASSWORD ", "
//                       TABLE_DATA "." TABLE_DATA_DESCRIPTION
//                       " FROM " TABLE_DATA " INNER JOIN " TABLE_USERS
//                       " ON (" TABLE_USERS".id = " TABLE_DATA ".account_id) WHERE "
//                       TABLE_DATA ".account_id = " + QString::number(currentUser->id) + ";");
//    sqlModel = getQueryModel();
//    model->setTable(TABLE_DATA);
//    model->select();
//    ui->tableView->setModel(sqlModel);
    updateTableViewModel(ui->tableView);
//    ui->tableView->hideColumn(0);
//    ui->tableView->hideColumn(1);

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
    AddEntry *addRow = new AddEntry(db, currentUser, this);
    addRow->show();
    updateTableViewModel(ui->tableView);

}


void DataWindow::on_pbCancel_clicked()
{
//    parentWidget()->show();
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
QSqlQueryModel *sqlmodel = new QSqlQueryModel(this);        // MEMORY LEAK
//        QSqlQueryModel *sqlmodel
//    model->setFilter("account_id = " + currentUser->id);
    sqlmodel->setQuery("SELECT " TABLE_DATA_TITLE ", "
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
