#ifndef WINDOWOPEN_H
#define WINDOWOPEN_H

#include <QMainWindow>
#include "sqlitedbmanager.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QApplication>
#include "initdialog.h"

namespace Ui {
class WindowOpen;
}

class WindowOpen : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowOpen(InitDialog *parent = nullptr);

    ~WindowOpen();

private slots:
    void on_pbCancel_clicked();

    void on_pbLogin_clicked();

private:
    Ui::WindowOpen *ui;
    SqliteDBManager *db;
    InitDialog *parentWin;
    void closeEvent (QCloseEvent *event);
};

#endif // WINDOWOPEN_H
