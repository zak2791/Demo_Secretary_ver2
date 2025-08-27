#include "system_0_common.h"
#include "qjsonarray.h"
#include "qjsondocument.h"

#include <QPainter>
#include <QComboBox>

System_0_Common::System_0_Common(QList<athlete> list, QJsonObject* _data){

    lAthletes = list;

    data = _data;

    for(int i = 0; i < list.count(); i++){
        lRectDraw.append(QRect(  0, i * 40, 40, 40));
        lRectName.append(QRect( 40, i * 40, 100, 40));
        lRectNameT.append(QRect( 40 + offsetText, i * 40, 100 - offsetText, 40));
        lRectTeam.append(QRect(140, i * 40, 100, 40));
        lRectTeamT.append(QRect(140 + offsetText, i * 40, 100 - offsetText, 40));
        lRectRange.append(QRect(240, i * 40, 40, 40));
        lRectRate.append(QRect(280, i * 40, 40, 40));
        lRectAddRate.append(QRect(320, i * 40, 40, 40));
        lRectPlace.append(QRect(360, i * 40, 40, 40));
        QString s = lAthletes.at(i).name.simplified();
        lAthletes[i].name = s.replace(s.indexOf(" "), 1, "\n");
        s = lAthletes.at(i).team.simplified();
        lAthletes[i].team = s.replace(s.indexOf(" "), 1, "\n");
        hoverPlaceFlags.append(false);
    }

    idPlace1 = (*data)["Place1"].toInt();
    if(idPlace1 > 0) currentListPlaces.append("1");
    idPlace2 = (*data)["Place2"].toInt();
    if(idPlace2 > 0) currentListPlaces.append("2");
    idPlace3 = (*data)["Place3"].toInt();
    if(idPlace3 > 0) currentListPlaces.append("3");
    idPlace4 = (*data)["Place4"].toInt();
    if(idPlace4 > 0) currentListPlaces.append("4");

    rectDraw = QRect(0, 0, 40, 40 * list.count());

    flagOnMat = (*data)["OnMat"].toBool();

    menu = new QMenu;
    setAcceptHoverEvents(true);
}

int System_0_Common::getHeight()
{
    return lAthletes.count() * 40;
}

void System_0_Common::setRates(QList<rates> list)
{
    // foreach(auto each, list){
    //     for(int i = 0; i < lAthletes.count(); i++){
    //         if(each.id == lAthletes.at(i).id){
    //             lAthletes[i].rate = each.rate;
    //             lAthletes[i].add_rate = each.add_rate;
    //         }
    //     }
    // }
}

void System_0_Common::cancelSendOnMat()
{
    (*data)["OnMat"] = false;
    flagOnMat = false;
    emit sigSaveData();
    update();
}

QRectF System_0_Common::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(penWidth / 2 - 10, penWidth / 2 - 10 - 40,
                  400 + penWidth + 20, 40 * lAthletes.count() + penWidth + 10 + 40);
}

void System_0_Common::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem*,
                            QWidget*)
{

    QFont f = painter->font();
    QFont newFont = painter->font();
    int size = newFont.pointSize();
    newFont.setPointSize(size * 0.8);
    painter->setFont(newFont);
    painter->drawRect(QRect(  0, -40,  40, 40));
    painter->drawText(QRect(  0, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "№\nп/п");
    painter->drawRect(QRect( 40, -40, 100, 40));
    painter->drawText(QRect( 40, -40, 100, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Спортсмен");
    painter->drawRect(QRect(140, -40, 100, 40));
    painter->drawText(QRect(140, -40, 100, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Команда");
    painter->drawRect(QRect(240, -40,  40, 40));
    painter->drawText(QRect(240, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Разряд");
    painter->drawRect(rSortRate);
    painter->drawText(rSortRate, Qt::AlignVCenter | Qt::AlignHCenter, "Оценка");
    painter->drawRect(QRect(320, -40,  40, 40));
    painter->drawText(QRect(320, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Доп.\nоценка");
    painter->drawRect(rSortPlace);
    painter->drawText(rSortPlace, Qt::AlignVCenter | Qt::AlignHCenter, "Место");

    painter->setFont(f);
    for(int i = 0; i < lAthletes.count(); i++){
        if(flagOnMat)
            painter->fillRect(lRectDraw.at(i), "lightgreen");
        else if(flagHoverDraw)
            painter->fillRect(lRectDraw.at(i), "lightgray");
        painter->drawRect(lRectDraw.at(i));
        painter->drawText(lRectDraw.at(i), Qt::AlignVCenter | Qt::AlignHCenter, QString::number(i + 1));
        painter->drawRect(lRectName.at(i));
        painter->drawText(lRectNameT.at(i), Qt::AlignVCenter | Qt::AlignLeft, lAthletes.at(i).name);
        painter->drawRect(lRectTeam.at(i));
        painter->drawText(lRectTeamT.at(i), Qt::AlignVCenter | Qt::AlignLeft, lAthletes.at(i).team);
        painter->drawRect(lRectRange.at(i));
        painter->drawText(lRectRange.at(i), Qt::AlignVCenter | Qt::AlignHCenter, lAthletes.at(i).range);
        painter->drawRect(lRectRate.at(i));
        painter->drawRect(lRectAddRate.at(i));

        if(hoverPlaceFlags.at(i))
            painter->fillRect(lRectPlace.at(i), "lightgray");
        else
            painter->drawRect(lRectPlace.at(i));

        for(int j = 0; j < lAthletes.count(); j++){
            if((*data)["Id"].toArray().at(j) == lAthletes.at(i).id){
                painter->drawText(lRectRate.at(i), Qt::AlignVCenter | Qt::AlignHCenter, QString::number((*data)["Rates"].toArray().at(j).toDouble()));
                painter->drawText(lRectAddRate.at(i), Qt::AlignVCenter | Qt::AlignHCenter, QString::number((*data)["AddRates"].toArray().at(j).toDouble()));

                if((*data)["Place1"] == (*data)["Id"][j]){
                    painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, "1");
                }
                else if((*data)["Place2"] == (*data)["Id"][j]){
                    painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, "2");
                }
                else if((*data)["Place3"] == (*data)["Id"][j]){
                    painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, "3");
                }
                else if((*data)["Place4"] == (*data)["Id"][j]){
                    painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, "4");
                }
            }
        }

    }
}

void System_0_Common::mousePressEvent(QGraphicsSceneMouseEvent* e){
    int x = e->pos().x();
    int y = e->pos().y();

    if(hoverPlaceFlags.contains(true)){
        menu->clear();
        menu->addAction(new QAction(""));

        for(int i = 1; i < 5; i++)
            if(!currentListPlaces.contains(QString::number(i)))
                menu->addAction(new QAction(QString::number(i)));

        QAction* act;
        act = menu->exec(QCursor::pos());

        if(act != nullptr){
            int index = hoverPlaceFlags.indexOf(true);
            int id = lAthletes[index].id;
            if(act->text() == ""){
                if(idPlace1 == id){
                    int ind = currentListPlaces.indexOf("1");
                    idPlace1 = -1;
                    (*data)["Place1"] = -1;
                    currentListPlaces.remove(ind);
                }
                else if(idPlace2 == id){
                    int ind = currentListPlaces.indexOf("2");
                    idPlace2 = -1;
                    (*data)["Place2"] = -1;
                    currentListPlaces.remove(ind);
                }
                else if(idPlace3 == id){
                    int ind = currentListPlaces.indexOf("3");
                    idPlace3 = -1;
                    (*data)["Place3"] = -1;
                    currentListPlaces.remove(ind);
                }
                else if(idPlace4 == id){
                    int ind = currentListPlaces.indexOf("4");
                    idPlace4 = -1;
                    (*data)["Place4"] = -1;
                    currentListPlaces.remove(ind);
                }
            }
            else if(act->text() == "1"){
                idPlace1 = id;
                (*data)["Place1"] = id;
                currentListPlaces.append("1");
                qDebug()<<"(*data)['Place1'] = "<<(*data)["Place1"]<<data;
            }
            else if(act->text() == "2"){
                idPlace2 = id;
                (*data)["Place2"] = id;
                currentListPlaces.append("2");
            }
            else if(act->text() == "3"){
                idPlace3 = id;
                (*data)["Place3"] = id;
                currentListPlaces.append("3");
            }
            else if(act->text() == "4"){
                idPlace4 = id;
                (*data)["Place4"] = id;
                currentListPlaces.append("4");
            }

            emit sigSaveData();

            update();
        }
        return;
    }

    if(rSortPlace.contains(x, y)){
        std::sort(lAthletes.begin(), lAthletes.end(), [this](const athlete &a1, const athlete &a2){
            QMap<QString, int> map;
            if(a1.id == (*data)["Place1"])
                map["1"] = 1;
            else if(a1.id == (*data)["Place2"])
                map["1"] = 2;
            else if(a1.id == (*data)["Place3"])
                map["1"] = 3;
            else if(a1.id == (*data)["Place4"])
                map["1"] = 4;
            else
                map["1"] = 5;
            if(a2.id == (*data)["Place1"])
                map["2"] = 1;
            else if(a2.id == (*data)["Place2"])
                map["2"] = 2;
            else if(a2.id == (*data)["Place3"])
                map["2"] = 3;
            else if(a2.id == (*data)["Place4"])
                map["2"] = 4;
            else
                map["2"] = 5;
            return map["1"] < map["2"];
        });
        return;
    }

    if(rSortRate.contains(x, y)){
        std::sort(lAthletes.begin(), lAthletes.end(), [this](const athlete &a1, const athlete &a2){
            QMap<QString, int> map;
            for(int i = 0; i < lAthletes.count(); i++){
                if((*data)["Id"][i] == a1.id)
                    map["1"] = (*data)["Rates"][i].toDouble();
                if((*data)["Id"][i] == a2.id){
                    map["2"] = (*data)["Rates"][i].toDouble();
                }
            }
            return map["1"] > map["2"];
        });
        return;
    }
    ///////////////////////////////////////////////
    if(flagHoverDraw && !flagOnMat){
        flagOnMat = true;
        (*data)["OnMat"] = true;
        emit sigSaveData();
        update();

        QJsonObject obj;
        QJsonArray arrId;
        QJsonArray arrNames;
        QJsonArray arrTeams;
        QJsonArray arrRanges;
        foreach(auto each, lAthletes){
            arrId.push_back(each.id);
            arrNames.push_back(each.name);
            arrTeams.push_back(each.team);
            arrRanges.push_back(each.range);
        }
        obj.insert("Id", arrId);
        obj.insert("Name", arrNames);
        obj.insert("Team", arrTeams);
        obj.insert("Range", arrRanges);
        QJsonDocument doc(obj);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        emit sigOnMat(0,        //режим - общий круг
                      strJson
                      );
    }
}

void System_0_Common::hoverMoveEvent(QGraphicsSceneHoverEvent* e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    for(int i = 0; i < lRectPlace.count(); i++){
        hoverPlaceFlags[i] = false;
        if(lRectPlace.at(i).contains(x, y)){
            hoverPlaceFlags[i] = true;
        }
    }

    if(rectDraw.contains(x, y))
        flagHoverDraw = true;
    else
        flagHoverDraw = false;

    update();
}
