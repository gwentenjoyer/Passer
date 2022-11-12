#ifndef WINDOWOPEN_H
#define WINDOWOPEN_H

#include <QMainWindow>

namespace Ui {
class WindowOpen;
}

class WindowOpen : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowOpen(QWidget *parent = nullptr);
    ~WindowOpen();

private:
    Ui::WindowOpen *ui;
};

#endif // WINDOWOPEN_H
