#include "system_0.h"

System_0::System_0(int _id, int _id_system, QList<athlete> list, QVariant _data)  : CompetitionSystem(_id, _id_system, list, _data){
    final_0 final_data = _data.value<final_0>();
    commonRoundItem = new System_0_Common(lAthlete);

    QList<athlete> lA{athlete(), athlete(), athlete(), athlete()};
    foreach(auto each, lAthlete){
        if(each.place == "1")
            lA[0] = each;
        else if(each.place == "2")
            lA[1] = each;
        else if(each.place == "3")
            lA[2] = each;
        else if(each.place == "4")
            lA[3] = each;
    }

    finalItem = new System_0_Final(lA, final_data);

    addItem(commonRoundItem);
    addItem(finalItem);

    finalItem->moveBy(0, commonRoundItem->getHeight() + 80);

    connect(commonRoundItem, SIGNAL(sigPlace(QList<athlete>)), this, SLOT(savePlace(QList<athlete>)));
    connect(commonRoundItem, SIGNAL(sigPlace(QList<athlete>)), finalItem, SLOT(setAthletes(QList<athlete>)));
}

void System_0::setRates(int _id, int _mode, QList<rates> _rates)
{
    if(_id == id){
        if(_mode == 0)
            commonRoundItem->setRates(_rates);
        else
            finalItem->setRates(_mode, _rates);
    }
}

void System_0::savePlace(QList<athlete> list)
{
    qDebug()<<list.count();
    foreach(auto each, list){
        qDebug()<<each.name;
    }
    //emit sigSaveData(id, id_system, 0, {QString::number(_id), str});
}

void System_0::cancelSendOnMat(int id, int mode)
{
    //emit sigSendOnMat(id, mode, list);
}
