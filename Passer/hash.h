#ifndef HASH_H
#define HASH_H

#include <qstring.h>
#include <qcryptographichash.h>

QString getHexHashOfQString(const QString &tobeHashed);


class Hash
{
public:
    Hash();
};

#endif // HASH_H
