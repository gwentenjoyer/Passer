#ifndef WINDOWCREATE_H
#define WINDOWCREATE_H

#include <QMainWindow>
#include "sqlitedbmanager.h"

namespace Ui {
class WindowCreate;
}

class WindowCreate : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowCreate(SqliteDBManager *dbIns, QWidget *parent = nullptr);
//    explicit WindowCreate(QWidget *parent = nullptr);
    ~WindowCreate();

private slots:
    void on_pbCancel_clicked();

private:
    Ui::WindowCreate *ui;
    SqliteDBManager *db;
};

#endif // WINDOWCREATE_H
