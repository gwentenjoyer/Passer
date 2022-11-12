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
//    bool choseOption();

private slots:

    void on_pbOpen_clicked();

    void on_pbCreate_clicked();

private:
    Ui::InitDialog *ui;
    bool optionChosen;
};
#endif // INITDIALOG_H