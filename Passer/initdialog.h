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
    InitDialog(QWidget *parent = nullptr);
    ~InitDialog();

private slots:

    void on_pbOpen_clicked();

    void on_pbCreate_clicked();

private:
    Ui::InitDialog *ui;
};
#endif // INITDIALOG_H
