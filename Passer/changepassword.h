#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include "sqlitedbmanager.h"
#include <QCloseEvent>
#include "ui_windowlogin.h"

namespace Ui {
class WindowLogin;
}

class ChangePassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangePassword(UserPublicData *upi, QWidget *parent = nullptr);

    ~ChangePassword();

private slots:
    void on_pbCancel_clicked();

    void on_pbContinue_clicked();
    void on_checkBox_stateChanged(int state);
private:
    Ui::WindowLogin *ui;
    SqliteDBManager *db;
    QWidget *parentWin;
    UserPublicData *currentUser;
    void closeEvent (QCloseEvent *event);
};


#endif // CHANGEPASSWORD_H
