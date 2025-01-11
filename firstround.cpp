#include "firstround.h"

#include <QPainter>
#include <QComboBox>

FirstRound::FirstRound(QList<athlete1round> list){
    lAthletes = list;

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

    // menu.addAction(new QAction(""));
    // menu.addAction(new QAction("4"));
    // menu.addAction(new QAction("1"));
    // menu.addAction(new QAction("2"));
    // menu.addAction(new QAction("3"));
    menu = new QMenu;

    setAcceptHoverEvents(true);
}

int FirstRound::getHeight()
{
    return lAthletes.count() * 40;
}

QRectF FirstRound::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(penWidth / 2 - 10, penWidth / 2 - 10 - 40,
                  400 + penWidth + 20, 40 * lAthletes.count() + penWidth + 10 + 40);
}

void FirstRound::paint(QPainter *painter,
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
        painter->drawText(lRectAddRate.at(i), Qt::AlignVCenter | Qt::AlignHCenter, lAthletes.at(i).addRate);
        if(hoverPlaceFlags.at(i))
            painter->fillRect(lRectPlace.at(i), "lightgray");
        else
            painter->drawRect(lRectPlace.at(i));
        painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, lAthletes.at(i).place);
    }
}

void FirstRound::mousePressEvent(QGraphicsSceneMouseEvent* e){
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
            emit sigPlace(lAthletes[index].id, lAthletes[index].place);
            update();
        }
        return;
    }
    if(rSortRate.contains(x, y)){
        std::sort(lAthletes.begin(), lAthletes.end(), [](const athlete1round &a1,
                                                     const athlete1round &a2){
            return a1.rate > a2.rate;
        });
        return;
    }
    if(rSortPlace.contains(x, y)){
        std::sort(lAthletes.begin(), lAthletes.end(), [](const athlete1round &a1,
                                                         const athlete1round &a2){
            if(a1.place == "" && a2.place == "")
                return true;
            if(a1.place == "")
                return false;
            if(a2.place == "")
                return true;
            //if(a1.place == "")
            return a1.place < a2.place;
            //else
            //    return a1.place > a2.place;
        });
        return;
    }
}

void FirstRound::hoverMoveEvent(QGraphicsSceneHoverEvent* e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    for(int i = 0; i < lRectPlace.count(); i++){
        hoverPlaceFlags[i] = false;
        if(lRectPlace.at(i).contains(x, y)){
            hoverPlaceFlags[i] = true;
        }
    }





    update();
}
