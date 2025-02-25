#ifndef SYSTEM_0_COMMON_H
#define SYSTEM_0_COMMON_H

#include "main.h"
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

class System_0_Common : public QGraphicsObject
{
    Q_OBJECT
public:
    System_0_Common(QList<athlete>, bool);
    int getHeight(void);
    void setRates(QList<rates>);
    void clearFlagOnMat(void){flagOnMat = false; update();}

private:
    QList<athlete> lAthletes;
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

    QVariant data;

    QStringList currentListPlaces;  //список с текущими установленными местами

    QList<bool> hoverPlaceFlags;    //список флагов наведения курсора на ячейку выбора места

    bool flagOnMat = false;         //флаг отправки на ковер

    QRect rectDraw;                 //область номеров жеребьевки
    bool flagHoverDraw = false;     //флаг наведения курсора на номера жеребьёвки

signals:
    void sigPlace(int, QString);
    void sigPlace(QList<athlete>);
    void sigOnMAt(int, QVariant);

};

#endif // SYSTEM_0_COMMON_H
