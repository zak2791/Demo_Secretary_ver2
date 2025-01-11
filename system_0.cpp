#include "commonroundhalffinaltwothird.h"

CommonRoundHalfFinalTwoThird::CommonRoundHalfFinalTwoThird(int _id, QList<athlete1round> list) {
    id = _id;
    id_system = 0;
    lAthlete = list;
    commonRoundItem = new FirstRound(lAthlete);
    finalItem = new ItemHalfAndFinalOne3;
    addItem(commonRoundItem);
    addItem(finalItem);
    finalItem->moveBy(0, commonRoundItem->getHeight() + 80);
    connect(commonRoundItem, SIGNAL(sigPlace(int, QString)), this, SLOT(savePlace(int, QString)));
}

void CommonRoundHalfFinalTwoThird::setResult(int, int, QList<QString>)
{

}

void CommonRoundHalfFinalTwoThird::savePlace(int _id, QString str)
{
    qDebug()<<_id<<str;
    emit sigSaveData(id, id_system, 0, {QString::number(_id), str});
}

void CommonRoundHalfFinalTwoThird::sendOnMat(int id, int mode, QList<QString> list)
{
    emit sigSendOnMat(id, mode, list);
}
