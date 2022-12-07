#include "initdialog.h"
#include <QApplication>
#include "windowcreate.h"
#include "sqlitedbmanager.h"
#include "dbmanager.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbManager *sqliteIns = SqliteDBManager::getInstance();
    sqliteIns->connectToDataBase();
    a.setWindowIcon(QIcon("..\\Passer\\winic32x32.ico"));
    InitDialog w;
    w.show();
    return a.exec();
}
