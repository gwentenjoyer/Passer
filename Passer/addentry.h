#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QMainWindow>
#include <QDialog>
#include "userinfo.h"
#include "ui_dataentry.h"

namespace Ui {
class EditEntry;
}

class AddEntry : public QDialog
{
    Q_OBJECT

public:
    explicit AddEntry(UserPublicData *currUser, QMainWindow *parent = nullptr);
    ~AddEntry();

private slots:
    void on_pbCancel_clicked();

    void on_pbProceed_clicked();

private:
    Ui::EditEntry *ui;
    UserPublicData *currUser;
    QMainWindow *parentWin;
};

#endif // ADDENTRY_H
