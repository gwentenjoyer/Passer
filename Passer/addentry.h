#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QMainWindow>
#include "sqlitedbmanager.h"
#include <QDialog>

namespace Ui {
class AddEntry;
}

class AddEntry : public QDialog
{
    Q_OBJECT

public:
    explicit AddEntry(SqliteDBManager *db, Users *currUser, QMainWindow *parent = nullptr);
    ~AddEntry();

private slots:
    void on_pbCancel_clicked();

    void on_pbAdd_clicked();


private:
    SqliteDBManager *db;
    Ui::AddEntry *ui;
    Users *currUser;
    QMainWindow *parentWin;

};

#endif // ADDENTRY_H
