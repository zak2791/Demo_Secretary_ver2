#ifndef FIRSTROUND_H
#define FIRSTROUND_H

#include "main.h"
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

class FirstRound : public QGraphicsObject
{
    Q_OBJECT
public:
    FirstRound(QList<athlete1round> = {});
    int getHeight(void);

private:
    QList<athlete1round> lAthletes;
    QRectF boundingRect(void) const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;

    int offsetText = 3;
    QList<QRect> lRectDraw;
    QList<QRect> lRectName;
    QList<QRect> lRectNameT;
    QList<QRect> lRectTeam;
    QList<QRect> lRectTeamT;
    QList<QRect> lRectRange;
    QList<QRect> lRectRate;
    QList<QRect> lRectAddRate;
    QList<QRect> lRectPlace;

    QRect rSortRate = QRect(280, -40,  40, 40);
    QRect rSortPlace = QRect(360, -40,  40, 40);

    QMenu* menu;

    QStringList currentListPlaces;  //список с текущими установленными местами

    QList<bool> hoverPlaceFlags; //список флагов наведения курсора на ячейку выбора места

signals:
    void sigPlace(int, QString);

};

#endif // FIRSTROUND_H
