#include "sqlitedbmanager.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QCryptographicHash>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager(){

}

SqliteDBManager::~SqliteDBManager() {
    closeDataBase();
    qDebug() << "Database disconnected.";
    delete instance;
}

SqliteDBManager* SqliteDBManager::getInstance()
{
    if(instance == nullptr){
        instance = new SqliteDBManager();
    }
    return instance;
}

void SqliteDBManager::connectToDataBase()
{
    if(QFile(DATABASE_NAME).exists()){
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

QSqlDatabase SqliteDBManager::getDB()
{
    return db;
}

bool SqliteDBManager::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTables()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Couldn't restore database " DATABASE_NAME "@" DATABASE_HOSTNAME ".";
        return false;
    }
}

bool SqliteDBManager::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        qDebug() << "Database " DATABASE_NAME "@" DATABASE_HOSTNAME " has successfully connected.";
        db.exec("PRAGMA foreign_keys=ON");
        return true;
    }
    else
        qDebug() << "Error occured while openning database " DATABASE_NAME "@" DATABASE_HOSTNAME ".";
    return false;
}

void SqliteDBManager::closeDataBase()
{
    db.close();
}

bool SqliteDBManager::createTables()
{
    QSqlQuery queryUsers, queryData;
    queryUsers.prepare("CREATE TABLE " TABLE_USERS " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                        TABLE_USERS_USER            " VARCHAR(32) UNIQUE NOT NULL,"
                        TABLE_USERS_PASSWORD        " VARCHAR(32)            NOT NULL"
                        ");");
    queryData.prepare("CREATE TABLE " TABLE_DATA " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                        "account_id INTEGER NOT NULL, "
                        TABLE_DATA_TITLE            " VARCHAR(32) UNIQUE NOT NULL CHECK( " TABLE_DATA_TITLE " <> ''), "
                        TABLE_DATA_URL              " VARCHAR NOT NULL CHECK( " TABLE_DATA_URL " <> ''), "
                        TABLE_DATA_USERNAME         " VARCHAR(32)  NOT NULL CHECK( " TABLE_DATA_USERNAME " <> ''), "
                        TABLE_DATA_PASSWORD         " VARCHAR(64) NOT NULL CHECK( " TABLE_DATA_PASSWORD " <> ''), "
                        TABLE_DATA_DESCRIPTION      " VARCHAR, "
                        "FOREIGN KEY(account_id) REFERENCES " TABLE_USERS "(id) ON UPDATE CASCADE ON DELETE CASCADE "
                        ");");

    if(!queryUsers.exec()){
        qDebug() << "DataBase: error of create " << TABLE_USERS;
        qDebug() << queryUsers.lastError().text() << ", caused by query:";
        qDebug() << queryUsers.lastQuery();
        return false;
    }
    else if(!queryData.exec()){
        qDebug() << "DataBase: error of create " << TABLE_DATA;
        qDebug() << queryData.lastError().text() << ", caused by query:";
        qDebug() << queryData.lastQuery();
        return false;
    }
    return true;
}

bool SqliteDBManager::insert(const UserInfo& userLoginData) {

    QSqlQuery query;
    if(userLoginData.getUsername() == "" || userLoginData.getPassword() == ""){
        throw (QString)"Fields cannot be empty.";
    }

    query.prepare("INSERT INTO " TABLE_USERS " ( " TABLE_USERS_USER ", "
                  TABLE_USERS_PASSWORD " ) "
                                        "VALUES (:User, :Password )");
    query.bindValue(":User",        userLoginData.getUsername());
    query.bindValue(":Password",       userLoginData.getPassword());

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE_USERS;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text();
//        return false;
    } else
        return true;
}

bool SqliteDBManager::insert(const UserPublicData *upi, const DataInfo& dataInfo) {
    QSqlQuery query;

    query.prepare("INSERT INTO " TABLE_DATA " ( account_id, "
                  TABLE_DATA_TITLE ", "
                  TABLE_DATA_URL " , "
                  TABLE_DATA_USERNAME " , "
                  TABLE_DATA_PASSWORD " , "
                  TABLE_DATA_DESCRIPTION " ) "
                                        "VALUES (:Acc_id, :Title, :Url, :Username, :Password, :Desc)");
    query.bindValue(":Acc_id",        upi->id);
    query.bindValue(":Title",        dataInfo.getTitle());
    query.bindValue(":Url",        dataInfo.getUrl());
    query.bindValue(":Username",        dataInfo.getUsername());
    query.bindValue(":Password",        dataInfo.getPassword());
    query.bindValue(":Desc",        dataInfo.getDescription());

    if(!query.exec()) {
        qDebug() << "error insert into " << TABLE_DATA;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text() + " caused by: " + query.lastQuery();
        return false;
    } else
        return true;
}

void SqliteDBManager::remove(int rowId) {
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE_DATA " WHERE id = " + QString::number(rowId) + ";");

    if(!query.exec()){
        qDebug() << "error deleting " << TABLE_DATA;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text() + " caused by: " + query.lastQuery();
    }
    qDebug() << "Successfully deleted row with id = " + QString::number(rowId);
}

void SqliteDBManager::remove(const UserPublicData *upi) {
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE_USERS " WHERE id = " + QString::number(upi->id) + ";");

    if(!query.exec()){
        qDebug() << "error deleting " << TABLE_USERS;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text() + " caused by: " + query.lastQuery();
    }
    qDebug() << "Successfully deleted user " << upi->username << " with id = " << QString::number(upi->id);
}

void SqliteDBManager::updateDataRow(const DataInfo &data){
    QSqlQuery query;

    query.prepare("UPDATE  " TABLE_DATA
                  " SET " TABLE_DATA_TITLE " = '" + data.getTitle() + "', "
                  " " TABLE_DATA_URL " = '" + data.getUrl() + "', "
                  " " TABLE_DATA_USERNAME " = '" + data.getUsername() + "', "
                  " " TABLE_DATA_PASSWORD " = '" + data.getPassword() + "', "
                  " " TABLE_DATA_DESCRIPTION " = '" + data.getDescription() + "' "
                  " WHERE id = " + QString::number(data.getId()) + ";");

    if(!query.exec()){
        qDebug() << "error updating " << TABLE_DATA;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text() + " caused by: " + query.lastQuery();
    }
    qDebug() << "Successfully updated row with id = " << data.getId();
}

UserPublicData* SqliteDBManager::searchForUser(const UserInfo& userInfo) {
    QSqlQuery query;

    if(userInfo.getUsername() == "" || userInfo.getPassword() == "")
        throw (QString)"Fields cannot be empty.";

    query.prepare("SELECT id, " TABLE_USERS_USER " FROM " TABLE_USERS
                  " WHERE " TABLE_USERS_USER " = :usr AND " TABLE_USERS_PASSWORD "  = :pswd;");
    query.bindValue(":usr", userInfo.getUsername());
    query.bindValue(":pswd", userInfo.getPassword());

    UserPublicData *user = nullptr;

    if (!query.exec()) {
        qDebug() << "Query failed!";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw (QString)"Error occured while proceeding query: " + query.lastError().text() + " \nQuery: " + query.lastQuery();
    } else {
        if (query.first()) { // get the first record in the result,
            qDebug() << query.first();
            user = new UserPublicData;       // POSSIBLE MEMORY LEAK
            user->id = query.value("id").toInt();
            user->username = query.value("user").toString();
        } else {
            qDebug () << "Data not found";
            throw (QString)"Cannot find user with this input data.";
        }
    }
    return user;
}

QSqlQueryModel* SqliteDBManager::getQueryModel(const UserPublicData *userPublicData, QObject *parent) {
// accout_id is hidden
QSqlQueryModel *sqlmodel = new QSqlQueryModel(parent);        // possible memory leak

    sqlmodel->setQuery("SELECT "
                   TABLE_DATA ".id, "
                   TABLE_DATA_TITLE ", "
                   TABLE_DATA "." TABLE_DATA_URL ", "
                   TABLE_DATA "." TABLE_DATA_USERNAME ", "
                   TABLE_DATA "." TABLE_DATA_PASSWORD ", "
                   TABLE_DATA "." TABLE_DATA_DESCRIPTION
                   " FROM " TABLE_DATA " INNER JOIN " TABLE_USERS
                   " ON (" TABLE_USERS".id = " TABLE_DATA ".account_id) WHERE "
                   TABLE_DATA ".account_id = " + QString::number(userPublicData->id) + ";");
    return sqlmodel;
}

QString SqliteDBManager::getPasswordHash(const UserPublicData *upi){
    QSqlQuery query;
    QString gottenHash;

    query.prepare("SELECT " TABLE_USERS_PASSWORD " FROM " TABLE_USERS
                  " WHERE " TABLE_USERS_USER " = :usr;");
    query.bindValue(":usr", upi->username);

    if (!query.exec()) {
        qDebug() << "Query failed!";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw (QString)"Error occured while proceeding query: " + query.lastError().text() + " \nQuery: " + query.lastQuery();
    } else {
        if (query.first()) {
            gottenHash = query.value(TABLE_USERS_PASSWORD).toString();
        } else {
            qDebug () << "Wrong user for getting password";
            throw (QString)"Wrong user for getting password";
        }
    }
    return gottenHash;
}

void SqliteDBManager::updatePasswordHash(const UserPublicData *user, const QString &newHash){
    QSqlQuery query;

    query.prepare("UPDATE  " TABLE_USERS
                  " SET " TABLE_USERS_PASSWORD " = '" + newHash + "' "
                  " WHERE id = '" + QString::number(user->id) + "';");

    if(!query.exec()){
        qDebug() << "error updating password " << TABLE_USERS;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text() + " caused by: " + query.lastQuery();
    }
    else {
        qDebug() << query.lastQuery();
        qDebug() << "Successfully updated password hash for user " << user->username;
    }
}
