#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include "userinfo.h"
#include "datainfo.h"
#include <qsqlquerymodel.h>

class DbManager
{
public:
    DbManager();

    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;
    virtual bool insert(const UserInfo&) = 0;
    virtual bool insert(const UserPublicData *upi,const DataInfo& dataInfo) = 0;
    virtual void remove(int rowId) = 0;
    virtual void remove(const UserPublicData *upi) = 0;
    virtual UserPublicData* searchForUser(const UserInfo& userInfo) = 0;
    virtual QSqlQueryModel* getQueryModel(const UserPublicData *userPublicData, QObject *parent) = 0;

    virtual QString getPasswordHash(const UserPublicData *upi) = 0;

    virtual void updatePasswordHash(const UserPublicData *user, const QString &newHash) = 0;

    virtual ~DbManager(){}

};

#endif // DBMANAGER_H
