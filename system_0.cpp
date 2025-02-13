#include "system_0.h"

System_0::System_0(int _id,
                   int _id_system,
                   int _status,
                   QList<athlete> list,
                   QVariant _data,
                   QString c,
                   QString a,
                   QString w)  :
    CompetitionSystem(_id, _id_system, _status, list, _data, c, a, w){

    final_0 final_data = _data.value<final_0>();        //?????????????????????????????????????error need json!!!!
    bool status;
    if(_status == 1 || _status == 3 || _status == 7)
        status = true;
    else
        status = false;
    commonRoundItem = new System_0_Common(lAthlete, status);

    QList<athlete> lA{athlete(), athlete(), athlete(), athlete()};
    foreach(auto each, lAthlete){
        QString s;
        if(each.place == "1"){
            s = each.name.simplified();
            lA[0].name = s.replace(s.indexOf(" "), 1, "\n");
            s = each.team.simplified();
            lA[0].team = s.replace(s.indexOf(" "), 1, "\n");
            lA[0].range = each.range;
        }
        else if(each.place == "2"){
            s = each.name.simplified();
            lA[1].name = s.replace(s.indexOf(" "), 1, "\n");
            s = each.team.simplified();
            lA[1].team = s.replace(s.indexOf(" "), 1, "\n");
            lA[1].range = each.range;
        }
        else if(each.place == "3"){
            s = each.name.simplified();
            lA[2].name = s.replace(s.indexOf(" "), 1, "\n");
            s = each.team.simplified();
            lA[2].team = s.replace(s.indexOf(" "), 1, "\n");
            lA[2].range = each.range;
        }
        else if(each.place == "4"){
            s = each.name.simplified();
            lA[3].name = s.replace(s.indexOf(" "), 1, "\n");
            s = each.team.simplified();
            lA[3].team = s.replace(s.indexOf(" "), 1, "\n");
            lA[3].range = each.range;
        }
    }

    finalItem = new System_0_Final(lA, final_data);

    addItem(commonRoundItem);
    addItem(finalItem);

    finalItem->moveBy(0, commonRoundItem->getHeight() + 80);

    connect(commonRoundItem, SIGNAL(sigPlace(int, QString)), this, SLOT(savePlace(int, QString)));
    connect(commonRoundItem, SIGNAL(sigPlace(QList<athlete>)), finalItem, SLOT(setAthletes(QList<athlete>)));
    connect(commonRoundItem, &System_0_Common::sigOnMAt, this, &System_0::sendOnMat);
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

void System_0::savePlace(int id_athlete, QString place)
{
    emit sigSaveData(id, id_system, 0, QVariant::fromValue(std::tuple<int, QString>{id_athlete, place}));
}

void System_0::sendOnMat(int mode, QVariant data)
{
    emit sigSendOnMat(id, id_system, mode, category, age, weight, data);
}

void System_0::cancelSendOnMat(int id, int mode)
{
    //emit sigSendOnMat(id, mode, list);
}
