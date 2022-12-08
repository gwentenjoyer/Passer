#ifndef WINDOWOPEN_H
#define WINDOWOPEN_H

#include <QMainWindow>
#include "sqlitedbmanager.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QApplication>
#include "initdialog.h"
#include "ui_windowlogin.h"

namespace Ui {
//class WindowOpen;
class WindowCreate;
}

class WindowOpen : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowOpen(InitDialog *parent = nullptr);

    ~WindowOpen();

private slots:
    void on_pbCancel_clicked();

//    void on_pbLogin_clicked();
    void on_pbContinue_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
//    Ui::WindowOpen *ui;
    Ui::WindowLogin *ui;
    SqliteDBManager *db;
    InitDialog *parentWin;
    void closeEvent (QCloseEvent *event);
};

#endif // WINDOWOPEN_H
