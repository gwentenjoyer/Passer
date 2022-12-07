#ifndef EDITENTRY_H
#define EDITENTRY_H

#include <QDialog>
#include <QVariantList>
#include "sqlitedbmanager.h"
#include "datainfo.h"

namespace Ui {
class EditEntry;
}

class EditEntry : public QDialog
{
    Q_OBJECT

public:
//    explicit EditEntry(SqliteDBManager *db, const QVariantList &list, QWidget *parent = nullptr);DataInfo
        explicit EditEntry(SqliteDBManager *db, const DataInfo &, QWidget *parent = nullptr);
    ~EditEntry();

private slots:
    void on_pbCancel_clicked();

    void on_pbEdit_clicked();

private:
    Ui::EditEntry *ui;
//    QVariantList list;
    DataInfo dataInfo;
    SqliteDBManager *db;
};

#endif // EDITENTRY_H
