#include "jsonconverter.h"
#include "main.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

JsonConverter::JsonConverter() {}

QVariant JsonConverter::jsonToQVariant(int system, QString val)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    // check validity of the document
    if(doc.isNull() || !doc.isObject())
        return QVariant();

    final_0 f_0 = final_0();
    obj = doc.object();

    switch (system) {
    case 0: 
        f_0.win_1 = obj.take("win_1").toInt();
        f_0.win_2 = obj.take("win_1").toInt();
        f_0.win_final = obj.take("win_1").toInt();
        f_0.win_third = obj.take("win_1").toInt();
        f_0.rate1 = obj.take("win_1").toString();
        f_0.rate2 = obj.take("win_1").toString();
        f_0.rate3 = obj.take("win_1").toString();
        f_0.rate4 = obj.take("win_1").toString();
        f_0.add_rate1 = obj.take("win_1").toString();
        f_0.add_rate2 = obj.take("win_1").toString();
        f_0.add_rate3 = obj.take("win_1").toString();
        f_0.add_rate4 = obj.take("win_1").toString();
        f_0.rate_fin1 = obj.take("win_1").toString();
        f_0.rate_fin2 = obj.take("win_1").toString();
        f_0.rate_third1 = obj.take("win_1").toString();
        f_0.rate_third2 = obj.take("win_1").toString();
        f_0.add_rate_fin1 = obj.take("win_1").toString();
        f_0.add_rate_fin2 = obj.take("win_1").toString();
        f_0.add_rate_third1 = obj.take("win_1").toString();
        f_0.add_rate_third2 = obj.take("win_1").toString();
        f_0.flag_on_mat_common = obj.take("win_1").toBool();
        f_0.flag_on_mat_half = obj.take("win_1").toBool();
        f_0.flag_on_mat_final = obj.take("win_1").toBool();
        return QVariant::fromValue(f_0);
        break;
    default:
        return QVariant();
        break;
    }
}

// QString JsonConverter::jsonToString(int, QJsonObject val)
// {

// }

// QJsonObject JsonConverter::stringToJsonSystem_0(QString val)
// {

// }

// QString JsonConverter::jsonToStringSystem_0(QJsonObject val)
// {

// }
