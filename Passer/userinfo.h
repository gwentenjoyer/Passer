#ifndef CLASSES_H
#define CLASSES_H

#include <qstring.h>

struct UserPublicData {
    int id;
    QString username;
//    QString password;
};

class UserInfo{
public:
    UserInfo(QString user, QString pswd);
    QString getUsername() const;
    QString getPassword() const;
private:
    QString username;
    QString password;
};

#endif // CLASSES_H
