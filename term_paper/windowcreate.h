#ifndef WINDOWCREATE_H
#define WINDOWCREATE_H

#include <QMainWindow>

namespace Ui {
class WindowCreate;
}

class WindowCreate : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowCreate(QWidget *parent = nullptr);
    ~WindowCreate();

private:
    Ui::WindowCreate *ui;
};

#endif // WINDOWCREATE_H
