#include "initdialog.h"

#include <QApplication>
#include "windowcreate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitDialog w;
    w.show();
//    if (w->choseOption()){
//        delete w;
//        WindowCreate *winCreate = new WindowCreate;
//        winCreate->show();
//    }
    return a.exec();
}
