#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVariantList>


/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOSTNAME               "localhost"
#define DATABASE_NAME                   "passerdb.sqlite"

#define TABLE_USERS                     "users"
#define TABLE_USERS_USER                "user"
#define TABLE_USERS_PASSWORD            "password"

#define TABLE_DATA                      "data"
#define TABLE_DATA_TITLE                "users"
#define TABLE_DATA_URL                  "url"
#define TABLE_DATA_USERNAME             "username"
#define TABLE_DATA_PASSWORD             "password"

class SqliteDBManager {

public:
    static SqliteDBManager* getInstance();

    /* Методи для безпосередньої роботи з класом
     * Підключення до бази даних і вставка записів у таблицю
     * */
    void connectToDataBase();
    QSqlDatabase getDB();
    bool inserIntoUsers(const QString tableName, const QVariantList &data);
    bool inserIntoData(const QString tableName, const QVariantList &data);

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
