#include "system_0.h"
#include "qjsonarray.h"
#include "qjsondocument.h"

System_0::System_0(int _id,
                   int _id_system,
                   QList<athlete> list,
                   QString _data,
                   QString c,
                   QString a,
                   QString w)  :
    CompetitionSystem(_id, _id_system, list, _data, c, a, w){

    //final_0 final_data = _data.value<final_0>();        //?????????????????????????????????????error need json!!!!
    //bool status;
    // if(_status == 1 || _status == 3 || _status == 7)
    //     status = true;
    // else
    //     status = false;
    qDebug()<<"_data = "<<_data;
    if(_data == "" || _data == "{}"){
        QJsonArray arrId;
        QJsonArray arrRates;
        QJsonArray arrAddRAtes;
        foreach (auto each, list) {
            arrId.push_back(each.id);
            arrRates.push_back(0.0);
            arrAddRAtes.push_back(0.0);
        }

        objCommon.insert("Id", arrId);
        objCommon.insert("Rates", arrRates);
        objCommon.insert("AddRates", arrAddRAtes);
        objCommon.insert("Place1", -1);
        objCommon.insert("Place2", -1);
        objCommon.insert("Place3", -1);
        objCommon.insert("Place4", -1);
        objCommon.insert("OnMat", false);

        objFinal.insert("WinnerHalf1", 0);
        objFinal.insert("WinnerHalf2", 0);
        objFinal.insert("WinnerFinal", 0);
        objFinal.insert("WinnerThird", 0);
        objFinal.insert("Rate1", 0.0);
        objFinal.insert("Rate2", 0.0);
        objFinal.insert("Rate3", 0.0);
        objFinal.insert("Rate4", 0.0);
        objFinal.insert("AddRate1", 0.0);
        objFinal.insert("AddRate2", 0.0);
        objFinal.insert("AddRate3", 0.0);
        objFinal.insert("AddRate4", 0.0);
        objFinal.insert("RateFinal1", 0.0);
        objFinal.insert("RateFinal2", 0.0);
        objFinal.insert("RateThird1", 0.0);
        objFinal.insert("RateThird2", 0.0);
        objFinal.insert("AddRateFinal1", 0.0);
        objFinal.insert("AddRateFinal2", 0.0);
        objFinal.insert("AddRateThird1", 0.0);
        objFinal.insert("AddRateThird2", 0.0);
        objFinal.insert("OnMatHalf", false);
        objFinal.insert("OnMatFinal", false);

        obj.insert("CommonData", objCommon);
        obj.insert("FinalData", objFinal);

        //data = strJson;
    }
    else{
        //data = _data;
        QJsonDocument doc = QJsonDocument::fromJson(_data.toUtf8());
        QJsonObject json = doc.object();
        objCommon = json["CommonData"].toObject();
        objFinal = json["FinalData"].toObject();
        obj.insert("CommonData", objCommon);
        obj.insert("FinalData", objFinal);
    }

    commonRoundItem = new System_0_Common(lAthlete, &objCommon);

    //QList<athlete> lA{athlete(), athlete(), athlete(), athlete()};
    // foreach(auto each, lAthlete){
    //     QString s;
    //     if(each.place == "1"){
    //         s = each.name.simplified();
    //         lA[0].name = s.replace(s.indexOf(" "), 1, "\n");
    //         s = each.team.simplified();
    //         lA[0].team = s.replace(s.indexOf(" "), 1, "\n");
    //         lA[0].range = each.range;
    //     }
    //     else if(each.place == "2"){
    //         s = each.name.simplified();
    //         lA[1].name = s.replace(s.indexOf(" "), 1, "\n");
    //         s = each.team.simplified();
    //         lA[1].team = s.replace(s.indexOf(" "), 1, "\n");
    //         lA[1].range = each.range;
    //     }
    //     else if(each.place == "3"){
    //         s = each.name.simplified();
    //         lA[2].name = s.replace(s.indexOf(" "), 1, "\n");
    //         s = each.team.simplified();
    //         lA[2].team = s.replace(s.indexOf(" "), 1, "\n");
    //         lA[2].range = each.range;
    //     }
    //     else if(each.place == "4"){
    //         s = each.name.simplified();
    //         lA[3].name = s.replace(s.indexOf(" "), 1, "\n");
    //         s = each.team.simplified();
    //         lA[3].team = s.replace(s.indexOf(" "), 1, "\n");
    //         lA[3].range = each.range;
    //     }
    // }

    finalItem = new System_0_Final(lAthlete, &objCommon, &objFinal);

    addItem(commonRoundItem);
    addItem(finalItem);

    finalItem->moveBy(0, commonRoundItem->getHeight() + 80);

    connect(commonRoundItem, SIGNAL(sigSaveData()), this, SLOT(saveData()));
    connect(commonRoundItem, SIGNAL(sigSaveData()), finalItem, SLOT(setAthletes()));
    connect(commonRoundItem, &System_0_Common::sigOnMat, this, &System_0::sendOnMat);

    connect(finalItem, &System_0_Final::sigSaveData, this, &System_0::saveData);
    connect(finalItem, &System_0_Final::sigOnMat, this, &System_0::sendOnMat);


}

void System_0::setRates(int _id, int _mode, QVariant _rates)
{
    if(_id == id){
        if(_mode == 0)
            commonRoundItem->setRates(qvariant_cast<QList<rates>>(_rates));
        else
            finalItem->setRates(_mode, qvariant_cast<QList<rates>>(_rates));
    }
}

void System_0::saveData()
{
    QJsonObject obj;
    obj.insert("CommonData", objCommon);
    obj.insert("FinalData", objFinal);
    QJsonDocument doc(obj);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    emit sigSaveData(id, strJson);
}

//////////////////////////////////////////////////////////////////////
/// \brief System_0::sendOnMat
/// \param mode 0 - первый круг, 1 - полуфиналы, 2 - финалы
/// \param data
//////////////////////////////////////////////////////////////////////
void System_0::sendOnMat(int mode, QString data)
{
    qDebug()<<"sentmat";
    emit sigSendOnMat(id, id_system, mode, category, age, weight, data);
}

void System_0::cancelSendOnMat(int _id, int mode)
{
    if(id == _id){
        if(mode == 0){
            commonRoundItem->cancelSendOnMat();
        }
        else if(mode == 1 || mode == 2){
            finalItem->cancelSendOnMat(mode);
        }
    }
}
