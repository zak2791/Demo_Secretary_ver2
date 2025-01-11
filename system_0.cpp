#include "system_0.h"

System_0::System_0(int _id, QList<athlete> list) {
    id = _id;
    id_system = 0;
    lAthlete = list;
    commonRoundItem = new FirstRound(lAthlete);
    finalItem = new ItemHalfAndFinalOne3();
    addItem(commonRoundItem);
    addItem(finalItem);
    finalItem->moveBy(0, commonRoundItem->getHeight() + 80);
    connect(commonRoundItem, SIGNAL(sigPlace(int, QString)), this, SLOT(savePlace(int, QString)));
}

void System_0::setResult(int, int, QList<QString>)
{

}

void System_0::savePlace(int _id, QString str)
{
    qDebug()<<_id<<str;
    emit sigSaveData(id, id_system, 0, {QString::number(_id), str});
}

void System_0::sendOnMat(int id, int mode, QList<QString> list)
{
    emit sigSendOnMat(id, mode, list);
}
