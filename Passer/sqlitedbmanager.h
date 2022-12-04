#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVariantList>

//#include <QSqlQuery>
//#include <QDebug>
//#include <QSqlError>

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

    void connectToDataBase();
    QSqlDatabase getDB();
    bool insertIntoUsers(const QString tableName, const QVariantList &data);
    bool insertIntoData(const QString tableName, Users *usr, const QVariantList &data);
    void deleteDataRow(int rowId);
    Users* searchForUser(const QVariantList &data);

    void updateDataRow(const QVariantList &data);


    //    Users* searchForUser(const QString user, const QString password);
    //    Users* searchForUser(const QVariantList &data);

    ~SqliteDBManager();

private:
    QSqlDatabase    db;

    static SqliteDBManager* instance;

    SqliteDBManager();

    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();

};



#endif // DATABASE_H
