#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QMainWindow>
#include <QDialog>
#include "userinfo.h"

namespace Ui {
class AddEntry;
}

class AddEntry : public QDialog
{
    Q_OBJECT

public:
    explicit AddEntry(UserPublicData *currUser, QMainWindow *parent = nullptr);
    ~AddEntry();

private slots:
    void on_pbCancel_clicked();

    void on_pbAdd_clicked();


private:
    Ui::AddEntry *ui;
    UserPublicData *currUser;
    QMainWindow *parentWin;

};

#endif // ADDENTRY_H
