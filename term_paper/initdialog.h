#ifndef INITDIALOG_H
#define INITDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class InitDialog; }
QT_END_NAMESPACE

class InitDialog : public QDialog
{
    Q_OBJECT

public:
    InitDialog(QWidget *parent = nullptr);
    ~InitDialog();

private:
    Ui::InitDialog *ui;
};
#endif // INITDIALOG_H
