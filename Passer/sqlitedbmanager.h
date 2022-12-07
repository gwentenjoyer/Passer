#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVariantList>

//#include <QSqlQuery>
//#include <QDebug>
//#include <QSqlError>

#define DATABASE_HOSTNAME               "localhost"
#define DATABASE_NAME                   "passerdb.sqlite"

#define TABLE_USERS                     "users"
#define TABLE_USERS_USER                "user"
#define TABLE_USERS_PASSWORD            "password_hash"

#define TABLE_DATA                      "data"
#define TABLE_DATA_TITLE                "title"
#define TABLE_DATA_URL                  "url"
#define TABLE_DATA_USERNAME             "username"
#define TABLE_DATA_PASSWORD             "password"
#define TABLE_DATA_DESCRIPTION          "description"

#include "userinfo.h"
#include "dbmanager.h"

class SqliteDBManager : public DbManager {

public:
    static SqliteDBManager* getInstance();
    void connectToDataBase();
    QSqlDatabase getDB();
//    bool insertIntoUsers(const QString tableName, const QVariantList &data);
//    bool insertIntoData(const QString tableName, Users *usr, const QVariantList &data);
    bool insert(const UserInfo&);
//    bool insert(const DataInfo&);
    bool insert(const UserPublicData *upi,const DataInfo& dataInfo);
    void deleteDataRow(int rowId);
    UserPublicData* searchForUser(const UserInfo& userInfo);
//    UserPublicData* searchForUser(const QVariantList &data);

//    void updateDataRow(const QVariantList &data);
    void updateDataRow(const DataInfo &data);


    //    Users* searchForUser(const QString user, const QString password);
    //    Users* searchForUser(const QVariantList &data);

    virtual ~SqliteDBManager() override;

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
