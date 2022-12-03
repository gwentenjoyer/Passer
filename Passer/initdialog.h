#ifndef INITDIALOG_H
#define INITDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include "sqlitedbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InitDialog; }
QT_END_NAMESPACE

class InitDialog : public QDialog
{
    Q_OBJECT

public:
    InitDialog(SqliteDBManager *dbIns, QWidget *parent = nullptr);
    ~InitDialog();
//    SqliteDBManager *db;
//    bool choseOption();

private slots:

    void on_pbOpen_clicked();

    void on_pbCreate_clicked();

private:
    Ui::InitDialog *ui;
    SqliteDBManager *db;
//    QMainWindow *wOpen;
//    QMainWindow *wCreate;
//    bool optionChosen;
};
#endif // INITDIALOG_H
