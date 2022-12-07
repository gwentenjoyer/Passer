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
    explicit EditEntry(const DataInfo &, QWidget *parent = nullptr);
    ~EditEntry();

private slots:
    void on_pbCancel_clicked();

    void on_pbEdit_clicked();

private:
    Ui::EditEntry *ui;
    DataInfo dataInfo;
};

#endif // EDITENTRY_H
