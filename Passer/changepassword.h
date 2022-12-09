#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QMainWindow>
#include "sqlitedbmanager.h"
#include <QCloseEvent>
#include "initdialog.h"
#include "ui_windowlogin.h"

namespace Ui {
class WindowLogin;
}

class ChangePassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangePassword(InitDialog *parent = nullptr);

    ~ChangePassword();

private slots:
    void on_pbCancel_clicked();

    void on_pbContinue_clicked();

private:
    Ui::WindowLogin *ui;
    SqliteDBManager *db;
    InitDialog *parentWin;
    void closeEvent (QCloseEvent *event);
};


#endif // CHANGEPASSWORD_H
