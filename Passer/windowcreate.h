#ifndef WINDOWCREATE_H
#define WINDOWCREATE_H

#include <QMainWindow>
#include "dbmanager.h"
#include <QCloseEvent>
#include "initdialog.h"
#include "ui_windowlogin.h"

namespace Ui {
class WindowLogin;
}

class WindowCreate : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowCreate(InitDialog *parent = nullptr);

    ~WindowCreate();

private slots:
    void on_pbCancel_clicked();

//    void on_pbSignin_clicked();

    void on_pbContinue_clicked();
    void on_checkBox_stateChanged(int state);

private:
    Ui::WindowLogin *ui;
    DbManager *db;
    InitDialog *parentWin;
    void closeEvent (QCloseEvent *event);
};

#endif // WINDOWCREATE_H
