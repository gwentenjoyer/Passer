#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVariantList>

//#include <QSqlQuery>
//#include <QDebug>
//#include <QSqlError>

/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOSTNAME               "localhost"
#define DATABASE_NAME                   "passerdb6.sqlite"

#define TABLE_USERS                     "users"
#define TABLE_USERS_USER                "user"
#define TABLE_USERS_PASSWORD            "password"

#define TABLE_DATA                      "data"
#define TABLE_DATA_TITLE                "title"
#define TABLE_DATA_URL                  "url"
#define TABLE_DATA_USERNAME             "username"
#define TABLE_DATA_PASSWORD             "password"
#define TABLE_DATA_DESCRIPTION          "description"

struct Users{
    int id;
    QString username;
//    QString password;
};

class SqliteDBManager {

public:
    static SqliteDBManager* getInstance();

    /* Методи для безпосередньої роботи з класом
     * Підключення до бази даних і вставка записів у таблицю
     * */


    void connectToDataBase();
    QSqlDatabase getDB();
    bool insertIntoUsers(const QString tableName, const QVariantList &data);
    bool insertIntoData(const QString tableName, Users *usr, const QVariantList &data);
    void deleteDataRow(int rowId);

    //    Users* searchForUser(const QString user, const QString password);
        Users* searchForUser(const QVariantList &data);
    //    Users* searchForUser(const QVariantList &data);

    ~SqliteDBManager(){
        qDebug() << "Database disconnected.";
        delete instance;
    }

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
