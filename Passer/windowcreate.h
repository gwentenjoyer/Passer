#ifndef WINDOWCREATE_H
#define WINDOWCREATE_H

#include <QMainWindow>
#include "sqlitedbmanager.h"
#include <QCloseEvent>
#include "initdialog.h"

namespace Ui {
class WindowCreate;
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

private:
    Ui::WindowCreate *ui;
    SqliteDBManager *db;
    InitDialog *parentWin;
    void closeEvent (QCloseEvent *event);
};

#endif // WINDOWCREATE_H
