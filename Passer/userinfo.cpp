#include "userinfo.h"


UserInfo::UserInfo(QString user, QString pswd) : username(user), password(pswd){}


QString UserInfo::getUsername() const {
    return this->username;
}
QString UserInfo::getPassword() const {
    return this->password;
}
