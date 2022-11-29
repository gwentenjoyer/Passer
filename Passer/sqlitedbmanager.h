//#ifndef SQLITEDBMANAGER_H
//#define SQLITEDBMANAGER_H


//class SqliteDbManager
//{
//public:
//    SqliteDbManager();
//};

//#endif // SQLITEDBMANAGER_H
#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVariantList>

//#include <dbmanager.h>

/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.db"

#define TABLE_EXAMPLE                   "TableExample"
#define TABLE_EXAMPLE_DATE              "Date"
#define TABLE_EXAMPLE_TIME              "Time"
#define TABLE_EXAMPLE_MESSAGE           "Message"
#define TABLE_EXAMPLE_RANDOM            "Random"

//class SqliteDBManager : public DBManager {
class SqliteDBManager {

public:
    static SqliteDBManager* getInstance();

    /* Методи для безпосередньої роботи з класом
     * Підключення до бази даних і вставка записів у таблицю
     * */
    void connectToDataBase();
    QSqlDatabase getDB();
    bool inserIntoTable(const QString tableName, const QVariantList &data);

private:
    // Сам об'єкт бази даних, з яким буде виконуватись робота
    QSqlDatabase    db;

private:

    static SqliteDBManager* instance;

    SqliteDBManager();

    /* Внутрішні методи для роботи з базою даних
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();
};



#endif // DATABASE_H
