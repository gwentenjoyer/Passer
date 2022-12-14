#include "hash.h"

Hash::Hash()
{

}

QString getHexHashOfQString(const QString &tobeHashed){

    QCryptographicHash returnHash(QCryptographicHash::Algorithm::Sha3_512);

    QByteArray bytes;
    bytes = returnHash.hash(tobeHashed.toLocal8Bit(), QCryptographicHash::Algorithm::Sha3_512);
//    qDebug() << QLatin1String(bytes.toHex()) << " and " << bytes.length();
    return QLatin1String(bytes.toHex());
}
