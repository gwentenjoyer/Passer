#include "sqlitedbmanager.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
//#include <QVector>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager(){

}

SqliteDBManager* SqliteDBManager::getInstance()
{
    if(instance == nullptr){
        instance = new SqliteDBManager();
    }
    return instance;
}




/* Методи для підключення до бази даних
 * */
void SqliteDBManager::connectToDataBase()
{
    /* Перед підключенням до бази даних виконуємо перевірку на її існування.
     * В залежності від результату виконуємо відкриття бази даних або її відновлення
     * */
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

/* Методи відновлення бази даних
 * */
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

/* Методи для відкриття бази даних
 * */
bool SqliteDBManager::openDataBase()
{
    /* База даних відкривається по вказаному шляху
     * і імені бази даних, якщо вона існує
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        qDebug() << "Database " DATABASE_NAME "@" DATABASE_HOSTNAME " has successfully connected.";
        return true;
    } else
        qDebug() << "Error occured while openning database " DATABASE_NAME "@" DATABASE_HOSTNAME ".";
        return false;
}

/* Метод закриття бази даних
 * */
void SqliteDBManager::closeDataBase()
{
    db.close();
}

/* Метод для створення таблиці в базі даних
 * */
bool SqliteDBManager::createTables()
{
    /* В даному випадку використовується фурмування сирого SQL-запиту
     * з наступним його виконанням.
     * */
    QSqlQuery queryUsers, queryData;
    queryUsers.prepare("CREATE TABLE " TABLE_USERS " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                        TABLE_USERS_USER            " VARCHAR(32) UNIQUE NOT NULL,"
                        TABLE_USERS_PASSWORD        " VARCHAR(32)            NOT NULL"
                        ");");
    queryData.prepare("CREATE TABLE " TABLE_DATA " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                        "account_id INTEGER NOT NULL, "
                        TABLE_DATA_TITLE            " VARCHAR(32)  NOT NULL, "
                        TABLE_DATA_URL              " VARCHAR NOT NULL, "
                        TABLE_DATA_USERNAME         " VARCHAR(32)  NOT NULL, "
                        TABLE_DATA_PASSWORD         " VARCHAR(32) NOT NULL, "
                        TABLE_DATA_DESCRIPTION      " VARCHAR, "
                        "FOREIGN KEY(account_id) REFERENCES " TABLE_USERS "(id) ON UPDATE CASCADE ON DELETE CASCADE"
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

/* Метод для вставки записів у базу даних
 * */
bool SqliteDBManager::insertIntoUsers(const QString tableName, const QVariantList &data)
{
    /* Запит SQL формується із QVariantList,
     * в який передаються данні для вставки в таблицю.
     * */
    QSqlQuery query;
    /* Спочатку SQL-запит формується з ключами,
     * які потім зв'язуються методом bindValue
     * для підставки даних із QVariantList
     * */
    QString username = data[0].toString(), password = data[1].toString();
    if(username == "" || password == ""){
        throw (QString)"Fields cannot be empty.";
    }

    if (tableName == TABLE_USERS){
//        qDebug() << tableName;
        query.prepare("INSERT INTO " TABLE_USERS " ( " TABLE_USERS_USER ", "
                      TABLE_USERS_PASSWORD " ) "
                                            "VALUES (:User, :Password )");
        query.bindValue(":User",        username);
        query.bindValue(":Password",       password);
    }

    // Після чого виконується запит методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << tableName;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw query.lastError().text();
//        return false;
    } else
        return true;
}

bool SqliteDBManager::insertIntoData(const QString tableName, const QVariantList &data)
{
    /* Запит SQL формується із QVariantList,
     * в який передаються данні для вставки в таблицю.
     * */
    QSqlQuery query;
    /* Спочатку SQL-запит формується з ключами,
     * які потім зв'язуються методом bindValue
     * для підставки даних із QVariantList
     * */
    if (tableName == TABLE_DATA){
//        qDebug() << tableName;
        query.prepare("INSERT INTO " TABLE_DATA " ( " TABLE_DATA_TITLE ", "
                      TABLE_DATA_URL " , "
                      TABLE_DATA_USERNAME " , "
                      TABLE_DATA_PASSWORD " ) "
                                            "VALUES (:Title, :Url, :Username, :Password)");
        query.bindValue(":Title",        data[0].toString());
        query.bindValue(":Url",        data[1].toString());
        query.bindValue(":Username",        data[2].toString());
        query.bindValue(":Password",        data[3].toString());
    }




    // Після чого виконується запит методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << tableName;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}

//    Users* searchForUser(const QString usr, const QString password){
Users* SqliteDBManager::searchForUser(const QVariantList &data){
    QSqlQuery query;

    QString username = data[0].toString(), password  = data[1].toString();
    if(username == "" || password == ""){
        throw (QString)"Fields cannot be empty.";
    }

    query.prepare("SELECT id, user, password"
                  " FROM " TABLE_USERS " WHERE user = :usr AND password = :pswd;");
    query.bindValue(":usr", data[0].toString());
    query.bindValue(":pswd", data[1].toString());
//        query.bindValue(":usr", usr);
//        query.bindValue(":pswd", password);
//    QList<Users> list;
    Users *user = nullptr;

    if (!query.exec()) {
        qDebug() << "Query failed!";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        throw (QString)"Error occured while proceeding query: " + query.lastError().text() + " \nQuery: " + query.lastQuery();
    } else {
        if (query.first()) { // get the first record in the result,
            qDebug() << query.first();
            user = new Users;       // POSSIBLE MEMORY LEAK
            user->id = query.value("id").toInt();
            user->username = query.value("user").toString();
//            user->password = query.value("password").toString();
//            list.append(user);
        } else {
            qDebug () << "Data not found";
            throw (QString)"Cannot find user with this input data.";
        }
    }
    return user;
}
