#ifndef DATAINFO_H
#define DATAINFO_H

#include <qstring.h>

class DataInfo{
public:
    DataInfo(const int &id, const QString &title, const QString &url,
             const QString &username, const QString &password, const QString &description);
    int getId() const;
    QString getTitle() const;
    QString getUrl() const;
    QString getUsername() const;
    QString getPassword() const;
    QString getDescription() const;

    void setId(const int &id);
    void setTitle(const QString &title);
    void setUrl(const QString &url);
    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void setDescription(const QString &desc);
private:
    int data_id;
    QString title;
    QString url;
    QString username;
    QString password;
    QString description;
};

#endif // DATAINFO_H
