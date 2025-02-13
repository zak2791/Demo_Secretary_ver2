#include "system_0_common.h"
#include "qjsonarray.h"

#include <QPainter>
#include <QComboBox>

System_0_Common::System_0_Common(QList<athlete> list, bool onMat){
    lAthletes = list;
    flagOnMat = onMat;
    QJsonArray jArr;
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
        if(lAthletes[i].place != "")
            currentListPlaces.append(lAthletes[i].place);
        QJsonObject jObj;
        jObj.insert("id", lAthletes.at(i).id);
        jObj.insert("name", lAthletes.at(i).name);
        jObj.insert("team", lAthletes.at(i).team);
        jObj.insert("range", lAthletes.at(i).range);
        jArr.append(jObj);
    }

    data = jArr.toVariantList();

    rectDraw = QRect(0, 0, 40, 40 * list.count());

    menu = new QMenu;
    setAcceptHoverEvents(true);
}

int System_0_Common::getHeight()
{
    return lAthletes.count() * 40;
}

void System_0_Common::setRates(QList<rates> list)
{
    foreach(auto each, list){
        for(int i = 0; i < lAthletes.count(); i++){
            if(each.id == lAthletes.at(i).id){
                lAthletes[i].rate = each.rate;
                lAthletes[i].add_rate = each.add_rate;
            }
        }
    }
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
        painter->drawText(lRectRate.at(i), Qt::AlignVCenter | Qt::AlignHCenter, lAthletes.at(i).rate);
        painter->drawRect(lRectAddRate.at(i));
        painter->drawText(lRectAddRate.at(i), Qt::AlignVCenter | Qt::AlignHCenter, lAthletes.at(i).add_rate);
        if(hoverPlaceFlags.at(i))
            painter->fillRect(lRectPlace.at(i), "lightgray");
        else
            painter->drawRect(lRectPlace.at(i));
        painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, lAthletes.at(i).place);
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
            QString place = lAthletes[index].place;
            if(place != ""){
                int ind = currentListPlaces.indexOf(place);
                currentListPlaces.remove(ind);
            }
            lAthletes[index].place = act->text();
            currentListPlaces.append(act->text());
            QList<athlete> lA{athlete(), athlete(), athlete(), athlete()};
            foreach(auto each, lAthletes){
                if(each.place == "1")
                    lA[0] = each;
                else if(each.place == "2")
                    lA[1] = each;
                else if(each.place == "3")
                    lA[2] = each;
                else if(each.place == "4")
                    lA[3] = each;
            }
            emit sigPlace(lA);                                  //установка спортсменов в финальной части
            emit sigPlace(lAthletes[index].id, act->text());    //запись в базу
            update();
        }
        return;
    }
    if(rSortRate.contains(x, y)){
        std::sort(lAthletes.begin(), lAthletes.end(), [](const athlete &a1,
                                                     const athlete &a2){
            return a1.rate > a2.rate;
        });
        return;
    }
    if(rSortPlace.contains(x, y)){
        std::sort(lAthletes.begin(), lAthletes.end(), [](const athlete &a1,
                                                         const athlete &a2){
            if(a1.place == "" && a2.place == "")
                return true;
            if(a1.place == "")
                return false;
            if(a2.place == "")
                return true;
            return a1.place < a2.place;
        });
        return;
    }
    if(flagHoverDraw && !flagOnMat){
        flagOnMat = true;

        emit sigOnMAt(0,        //режим - общий круг
                      data
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
