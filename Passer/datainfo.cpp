#include "datainfo.h"


DataInfo::DataInfo(const int &id, const QString &title, const QString &url,
                    const QString &username, const QString &password, const QString &description)
                    : data_id(id),
                    title(title),
                    url(url),
                    username(username),
                    password(password),
                    description(description)
{}

int DataInfo::getId() const{
    return this->data_id;
}
QString DataInfo::getTitle() const{
    return this->title;
}
QString DataInfo::getUrl() const{
    return this->url;
}
QString DataInfo::getUsername() const{
    return this->username;
}
QString DataInfo::getPassword() const{
    return this->password;
}
QString DataInfo::getDescription() const{
    return this->description;
}

void DataInfo::setId(const int &id) {
    this->data_id = id;
}
void DataInfo::setTitle(const QString &title) {
    this->title = title;
}
void DataInfo::setUrl(const QString &url) {
    this->url = url;
}
void DataInfo::setUsername(const QString &username){
    this->username = username;
}
void DataInfo::setPassword(const QString &password) {
    this->password = password;
}
void DataInfo::setDescription(const QString &desc){
    this->description = desc;
}
