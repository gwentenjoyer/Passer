#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QMainWindow>
#include "sqlitedbmanager.h"
#include <QMainWindow>

#include <QSqlQueryModel>
#include <QTableView>
#include "addentry.h"

#include <qmenu.h>
#include <qclipboard.h>

namespace Ui {
class DataWindow;
}

class DataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataWindow(UserPublicData *currUser, QMainWindow *parent = nullptr);
    ~DataWindow();

private slots:
    void on_pbQuit_clicked();

    void on_pbAdd_clicked();

    void on_pbCancel_clicked();

    void tableRefresh();

    void on_pbDelete_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pbEdit_clicked();

    void customContextMenuProceed(QPoint pos);
    void copySlot();

    void on_pbDeleteUser_clicked();

    void on_pbChangePassword_clicked();

private:
    Ui::DataWindow *ui;
    UserPublicData *currentUser;
    QMainWindow *parentWin;
    SqliteDBManager *db;
    QSqlQueryModel *sqlModel;
    QMenu menu;
    QAction act;
    QPoint selectedCell;
    AddEntry *winadd;
    void closeEvent (QCloseEvent *event);

//    QSqlQueryModel* getQueryModel();
    void updateTableViewModel(QTableView *tb);

    int tableSelectedRowDataId;
    int selectedRow;

    DataInfo getInfoFromDataSelectedRow(QTableView *table);

};

#endif // DATAWINDOW_H
