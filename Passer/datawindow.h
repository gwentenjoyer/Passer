#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QMainWindow>
#include "sqlitedbmanager.h"
#include <QMainWindow>

#include <QSqlQueryModel>
#include <QTableView>
#include "addentry.h"

namespace Ui {
class DataWindow;
}

class DataWindow : public QMainWindow
{
    Q_OBJECT

public:
//    explicit DataWindow(SqliteDBManager *dbIns, Users *currUser, QWidget *parent = nullptr);
    explicit DataWindow(SqliteDBManager *dbIns, Users *currUser, QMainWindow *parent = nullptr);
    ~DataWindow();
    friend AddEntry::~AddEntry();

private slots:
    void on_pbQuit_clicked();

    void on_pbAdd_clicked();

    void on_pbCancel_clicked();

    void on_pbRefresh_clicked();

    void on_pbDelete_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::DataWindow *ui;
    Users *currentUser;
    QMainWindow *parentWin;
    SqliteDBManager *db;
    QSqlQueryModel *sqlModel;

    void closeEvent (QCloseEvent *event);

    QSqlQueryModel* getQueryModel();
    void updateTableViewModel(QTableView *tb);
    int tableSelectedRowDataId;
//    friend class AddEntry;
};

#endif // DATAWINDOW_H
