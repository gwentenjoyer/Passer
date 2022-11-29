#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QMainWindow>

namespace Ui {
class AddEntry;
}

class AddEntry : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddEntry(QWidget *parent = nullptr);
    ~AddEntry();

private slots:
    void on_pbCancel_clicked();

private:
    Ui::AddEntry *ui;
};

#endif // ADDENTRY_H
