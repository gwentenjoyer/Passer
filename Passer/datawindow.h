#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QMainWindow>
#include "sqlitedbmanager.h"
#include <QMainWindow>

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

private slots:
    void on_pbQuit_clicked();

    void on_pbAdd_clicked();

    void on_pbCancel_clicked();

private:
    Ui::DataWindow *ui;
    Users *currentUser;
    QMainWindow *parentWin;
    SqliteDBManager *db;

    void closeEvent (QCloseEvent *event);
};

#endif // DATAWINDOW_H
