#include "initdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitDialog w;
    w.show();
    return a.exec();
}
