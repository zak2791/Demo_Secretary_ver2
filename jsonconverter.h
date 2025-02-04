#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

//#include "qjsonobject.h"

#include "qvariant.h"
class JsonConverter
{
public:
    JsonConverter();

    static QVariant jsonToQVariant(int, QString);
//     static QString jsonToString(int, QJsonObject);

// private:
//     static QJsonObject stringToJsonSystem_0(QString);
//     static QString jsonToStringSystem_0(QJsonObject);
};

#endif // JSONCONVERTER_H
