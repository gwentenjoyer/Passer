#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include "userinfo.h"
#include "datainfo.h"

class DbManager
{
public:
    DbManager();

    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;
    virtual bool insert(const UserInfo&) = 0;
    virtual bool insert(const UserPublicData *upi,const DataInfo& dataInfo) = 0;
    virtual void deleteDataRow(int rowId) = 0;
    virtual UserPublicData* searchForUser(const UserInfo& userInfo) = 0;

    virtual ~DbManager(){}

};

#endif // DBMANAGER_H
