#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>


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
#include <qsqlquerymodel.h>

class SqliteDBManager : public DbManager {

public:
    static SqliteDBManager* getInstance();
    void connectToDataBase();
    QSqlDatabase getDB();
    bool insert(const UserInfo&);
    bool insert(const UserPublicData *upi,const DataInfo& dataInfo);
    void remove(int rowId);
    void remove(const UserPublicData *upi);
    UserPublicData* searchForUser(const UserInfo& userInfo);
    void updateDataRow(const DataInfo &data);
    QSqlQueryModel* getQueryModel(const UserPublicData *userPublicData, QObject *parent = nullptr);
    QString getPasswordHash(const UserPublicData *upi);
    void updatePasswordHash(const UserPublicData *user, const QString &newHash);
    ~SqliteDBManager() override;


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
