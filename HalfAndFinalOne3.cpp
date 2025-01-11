#include "HalfAndFinalOne3.h"

#include <QPainter>

ItemHalfAndFinalOne3::ItemHalfAndFinalOne3(QList<athlete> aList,
                                           QList<rates> rList,
                                           QList<int> winners,
                                           QList<bool> onmat) {

    setAthletes(aList);
    setRates(rList);

    if(winners.count() == 4){
        winnerHalfOne = winners.at(0);
        if(winnerHalfOne == 1){
            drawFin1 = "1";
            drawThird1 = "3";
        }else if(winnerHalfOne == 2){
            drawFin1 = "3";
            drawThird1 = "1";
        }

        winnerHalfTwo = winners.at(1);
        if(winnerHalfTwo == 1){
            drawFin2 = "2";
            drawThird2 = "4";
        }else if(winnerHalfTwo == 2){
            drawFin2 = "4";
            drawThird2 = "2";
        }

        winnerFinal   = winners.at(2);
        if(winnerFinal == 1){
            drawFinal = drawFin1;
        }else if(winnerFinal == 2){
            drawFinal = drawFin2;
        }

        winnerThird   = winners.at(3);
        if(winnerThird == 1){
            drawThird = drawThird1;
        }else if(winnerThird == 2){
            drawThird = drawThird2;
        }
    }

    if(onmat.count() == 2){
        flagOnMatHalf  = onmat.at(0);
        flagOnMatFinal = onmat.at(1);
    }

    setAcceptHoverEvents(true);

    win              = new QImage(":/images/win.png");
    win_hover        = new QImage(":/images/win_hover.png");
    win_gray         = new QImage(":/images/win_gray.png");
    win_gray_hover   = new QImage(":/images/win_gray_hover.png");

}

QRectF ItemHalfAndFinalOne3::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(penWidth / 2 - 10, penWidth / 2 - 10,
                  680 + penWidth + 10, 440 + penWidth + 10);
}

void ItemHalfAndFinalOne3::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem*,
                                 QWidget*)
{
    if(flagOnMatHalf){
        painter->fillRect(rectHalf1, "gray");
        painter->fillRect(rectHalf3, "gray");
        painter->fillRect(rectHalf2, "gray");
        painter->fillRect(rectHalf4, "gray");
    }
    else{
        if(flagHoverHalf){
            painter->fillRect(rectHalf1, "darkgray");
            painter->fillRect(rectHalf3, "darkgray");
            painter->fillRect(rectHalf2, "darkgray");
            painter->fillRect(rectHalf4, "darkgray");
        }
        else{
            painter->drawRect(rectHalf1);
            painter->drawRect(rectHalf3);
            painter->drawRect(rectHalf2);
            painter->drawRect(rectHalf4);
        }
    }

    if(flagOnMatFinal){
        painter->fillRect(rectFin1,    "gray");
        painter->fillRect(rectFin2,    "gray");
        painter->fillRect(rectThird1, "gray");
        painter->fillRect(rectThird2, "gray");
    }
    else{
        if(flagHoverFinal){
            painter->fillRect(rectFin1,    "darkgray");
            painter->fillRect(rectFin2,   "darkgray");
            painter->fillRect(rectThird1, "darkgray");
            painter->fillRect(rectThird2, "darkgray");
        }
        else{
            painter->drawRect(rectFin1);
            painter->drawRect(rectFin2);
            painter->drawRect(rectThird1);
            painter->drawRect(rectThird2);
        }
    }

    for(int y = 0; y < 241; y+=80){
        painter->drawRect(40,  y, 100, 40);
        painter->drawRect(140, y, 100, 40);
        painter->drawRect(240, y, 40, 40);
        painter->drawRect(280, y, 40, 40);
        painter->drawRect(320, y, 40, 40);
        painter->drawRect(360, y, 40, 40);
    }
    for(int y = 40; y < 201; y+=160){
        //painter->drawRect(400,   y, 40, 40);
        painter->drawRect(440,  y, 40, 40);
        painter->drawRect(480, y, 40, 40);
        painter->drawRect(520, y, 40, 40);
    }
    for(int y = 320; y < 440; y+=80){
        //painter->drawRect(400,   y, 40, 40);
        painter->drawRect(440,  y, 40, 40);
        painter->drawRect(480, y, 40, 40);
        painter->drawRect(520, y, 40, 40);
    }
    painter->drawText(QRect(0,   0,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "1");
    painter->drawText(QRect(0,  80,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "3");
    painter->drawText(QRect(0, 160,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "2");
    painter->drawText(QRect(0, 240,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "4");

    painter->drawText(QRect(40 + 3,   0, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, name1);
    painter->drawText(QRect(40 + 3,  80, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, name3);
    painter->drawText(QRect(40 + 3, 160, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, name2);
    painter->drawText(QRect(40 + 3, 240, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, name4);

    painter->drawText(QRect(140 + 3,   0, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, team1);
    painter->drawText(QRect(140 + 3,  80, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, team3);
    painter->drawText(QRect(140 + 3, 160, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, team2);
    painter->drawText(QRect(140 + 3, 240, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, team4);

    painter->drawText(QRect(240,   0,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, range1);
    painter->drawText(QRect(240,  80,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, range3);
    painter->drawText(QRect(240, 160,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, range2);
    painter->drawText(QRect(240, 240,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, range4);

    painter->drawText(QRect(280,   0,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, rate1);
    painter->drawText(QRect(280,  80,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, rate3);
    painter->drawText(QRect(280, 160,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, rate2);
    painter->drawText(QRect(280, 240,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, rate4);

    painter->drawText(QRect(320,   0,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, addRate1);
    painter->drawText(QRect(320,  80,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, addRate3);
    painter->drawText(QRect(320, 160,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, addRate2);
    painter->drawText(QRect(320, 240,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, addRate4);

    painter->drawText(QRect(440,  40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, rateFin1);
    painter->drawText(QRect(440, 200,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, rateFin2);
    painter->drawText(QRect(440, 320,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, rateThird1);
    painter->drawText(QRect(440, 400,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, rateThird2);

    painter->drawText(QRect(480,  40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, addRateFin1);
    painter->drawText(QRect(480, 200,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, addRateFin2);
    painter->drawText(QRect(480, 320,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, addRateThird1);
    painter->drawText(QRect(480, 400,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, addRateThird2);

    painter->drawText(rectFin1, Qt::AlignVCenter | Qt::AlignHCenter, drawFin1);

    painter->drawText(rectFin2, Qt::AlignVCenter | Qt::AlignHCenter, drawFin2);

    painter->drawLine(560, 40, 560, 200);

    painter->drawRect(560, 120, 40, 40);
    painter->drawText(QRect(560, 120,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, drawFinal);
    painter->drawText(QRect(600 + 3, 120,  80, 40), Qt::AlignVCenter | Qt::AlignLeft, "1 место");

    painter->drawRect(560, 360, 40, 40);
    painter->drawText(rectThird1, Qt::AlignVCenter | Qt::AlignHCenter, drawThird1);
    painter->drawText(rectThird2, Qt::AlignVCenter | Qt::AlignHCenter, drawThird2);
    painter->drawText(QRect(560, 360,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, drawThird);
    painter->drawText(QRect(600 + 3, 360,  80, 40), Qt::AlignVCenter | Qt::AlignLeft, "3 место");

    if(flagHoverWin1){
        if(winnerHalfOne == 0)
            painter->drawImage(rectWinHalf1, *win_gray_hover);
        else if(winnerHalfOne == 1)
            painter->drawImage(rectWinHalf1, *win_hover);
        else
            painter->drawImage(rectWinHalf1, *win_gray);
    }
    else{
        if(winnerHalfOne == 1)
            painter->drawImage(rectWinHalf1, *win);
        else
            painter->drawImage(rectWinHalf1, *win_gray);
    }
    if(flagHoverWin2){
        if(winnerHalfOne == 0)
            painter->drawImage(rectWinHalf3, *win_gray_hover);
        else if(winnerHalfOne == 2)
            painter->drawImage(rectWinHalf3, *win_hover);
        else
            painter->drawImage(rectWinHalf3, *win_gray);
    }
    else{
        if(winnerHalfOne == 2)
            painter->drawImage(rectWinHalf3, *win);
        else
            painter->drawImage(rectWinHalf3, *win_gray);
    }
    if(flagHoverWin3){
        if(winnerHalfTwo == 0)
            painter->drawImage(rectWinHalf2, *win_gray_hover);
        else if(winnerHalfTwo == 1)
            painter->drawImage(rectWinHalf2, *win_hover);
        else
            painter->drawImage(rectWinHalf2, *win_gray);
    }
    else{
        if(winnerHalfTwo == 1)
            painter->drawImage(rectWinHalf2, *win);
        else
            painter->drawImage(rectWinHalf2, *win_gray);
    }
    if(flagHoverWin4){
        if(winnerHalfTwo == 0)
            painter->drawImage(rectWinHalf4, *win_gray_hover);
        else if(winnerHalfTwo == 2)
            painter->drawImage(rectWinHalf4, *win_hover);
        else
            painter->drawImage(rectWinHalf4, *win_gray);
    }
    else{
        if(winnerHalfTwo == 2)
            painter->drawImage(rectWinHalf4, *win);
        else
            painter->drawImage(rectWinHalf4, *win_gray);
    }
    if(flagHoverWinHalf1){
        if(winnerFinal == 0)
            painter->drawImage(rectWinFin1, *win_gray_hover);
        else if(winnerFinal == 1)
            painter->drawImage(rectWinFin1, *win_hover);
        else
            painter->drawImage(rectWinFin1, *win_gray);
    }
    else{
        if(winnerFinal == 1)
            painter->drawImage(rectWinFin1, *win);
        else
            painter->drawImage(rectWinFin1, *win_gray);
    }
    if(flagHoverWinHalf2){
        if(winnerFinal == 0)
            painter->drawImage(rectWinFin2, *win_gray_hover);
        else if(winnerFinal == 2)
            painter->drawImage(rectWinFin2, *win_hover);
        else
            painter->drawImage(rectWinFin2, *win_gray);
    }
    else{
        if(winnerFinal == 2)
            painter->drawImage(rectWinFin2, *win);
        else
            painter->drawImage(rectWinFin2, *win_gray);
    }
    if(flagHoverWinThird1){
        if(winnerThird == 0)
            painter->drawImage(rectWinThird1, *win_gray_hover);
        else if(winnerThird == 1)
            painter->drawImage(rectWinThird1, *win_hover);
        else
            painter->drawImage(rectWinThird1, *win_gray);
    }
    else{
        if(winnerThird == 1)
            painter->drawImage(rectWinThird1, *win);
        else
            painter->drawImage(rectWinThird1, *win_gray);
    }
    if(flagHoverWinThird2){
        if(winnerThird == 0)
            painter->drawImage(rectWinThird2, *win_gray_hover);
        else if(winnerThird == 2)
            painter->drawImage(rectWinThird2, *win_hover);
        else
            painter->drawImage(rectWinThird2, *win_gray);
    }
    else{
        if(winnerThird == 2)
            painter->drawImage(rectWinThird2, *win);
        else
            painter->drawImage(rectWinThird2, *win_gray);
    }

}

void ItemHalfAndFinalOne3::setAthletes(QList<athlete> aList)
{
    if(aList.count() == 4){
        name1 = aList.at(0).name.simplified();
        name1 = name1.replace(name1.indexOf(" "), 1, "\n");
        name3 = aList.at(1).name;
        name3 = name3.replace(name3.indexOf(" "), 1, "\n");
        name2 = aList.at(2).name;
        name2 = name2.replace(name2.indexOf(" "), 1, "\n");
        name4 = aList.at(3).name;
        name4 = name4.replace(name4.indexOf(" "), 1, "\n");

        team1 = aList.at(0).team;
        team1 = team1.replace(team1.indexOf(" "), 1, "\n");
        team3 = aList.at(1).team;
        team3 = team3.replace(team3.indexOf(" "), 1, "\n");
        team2 = aList.at(2).team;
        team2 = team2.replace(team2.indexOf(" "), 1, "\n");
        team4 = aList.at(3).team;
        team4 = team4.replace(team4.indexOf(" "), 1, "\n");

        range1 = aList.at(0).range;
        range3 = aList.at(1).range;
        range2 = aList.at(2).range;
        range4 = aList.at(3).range;
    }
}

void ItemHalfAndFinalOne3::setAthlete(int draw, athlete athl)
{
    if(draw == 1){
        name1 = athl.name.simplified();
        name1 = name1.replace(name1.indexOf(" "), 1, "\n");
        team1 = athl.team;
        team1 = team1.replace(team1.indexOf(" "), 1, "\n");
        range1 = athl.range;
    }
    else if(draw == 2){
        name2 = athl.name.simplified();
        name2 = name2.replace(name2.indexOf(" "), 1, "\n");
        team2 = athl.team;
        team2 = team2.replace(team2.indexOf(" "), 1, "\n");
        range2 = athl.range;
    }
    else if(draw == 3){
        name3 = athl.name.simplified();
        name3 = name3.replace(name3.indexOf(" "), 1, "\n");
        team3 = athl.team;
        team3 = team3.replace(team3.indexOf(" "), 1, "\n");
        range3 = athl.range;
    }
    else{
        name4 = athl.name.simplified();
        name4 = name4.replace(name4.indexOf(" "), 1, "\n");
        team4 = athl.team;
        team4 = team4.replace(team4.indexOf(" "), 1, "\n");
        range4 = athl.range;
    }
}

void ItemHalfAndFinalOne3::setRates(QList<rates> rList)
{
    if(rList.count() == 8){
        rate1           = rList.at(0).rate;
        addRate1        = rList.at(0).addRate;
        rate3           = rList.at(1).rate;
        addRate3        = rList.at(1).addRate;
        rate2           = rList.at(2).rate;
        addRate2        = rList.at(2).addRate;
        rate4           = rList.at(3).rate;
        addRate4        = rList.at(3).addRate;
        rateFin1        = rList.at(4).rate;
        addRateFin1     = rList.at(4).addRate;
        rateFin2        = rList.at(5).rate;
        addRateFin2     = rList.at(5).addRate;
        rateThird1      = rList.at(6).rate;
        addRateThird1   = rList.at(6).addRate;
        rateThird2      = rList.at(7).rate;
        addRateThird2   = rList.at(7).addRate;
    }
}

void ItemHalfAndFinalOne3::cancelSendOnMat(int onmat)
{
    if(onmat == 0)
        flagOnMatHalf  = false;
    else
        flagOnMatFinal = false;
}

void ItemHalfAndFinalOne3::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    /*Выбор победителей*/
    if(rectWinHalf1.contains(x, y)){
        if(winnerHalfOne == 0){
            winnerHalfOne = 1;
            drawFin1 = "1";
            drawThird1 = "3";
            emit sigPressWinner(0, true);
        }
        else if (winnerHalfOne == 1){
            winnerHalfOne = 0;
            drawFin1 = "";
            drawThird1 = "";
            emit sigPressWinner(0, false);
        }
    }
    else if(rectWinHalf3.contains(x, y)){
        if(winnerHalfOne == 0){
            winnerHalfOne = 2;
            drawFin1 = "3";
            drawThird1 = "1";
            emit sigPressWinner(1, true);
        }
        else if (winnerHalfOne == 2){
            winnerHalfOne = 0;
            drawFin1 = "";
            drawThird1 = "";
            emit sigPressWinner(1, false);
        }
    }
    else if(rectWinHalf2.contains(x, y)){
        if(winnerHalfTwo == 0){
            winnerHalfTwo = 1;
            drawFin2 = "2";
            drawThird2 = "4";
            emit sigPressWinner(2, true);
        }
        else if (winnerHalfTwo == 1){
            winnerHalfTwo = 0;
            drawFin2 = "";
            drawThird2 = "";
            emit sigPressWinner(2, false);
        }
    }
    else if(rectWinHalf4.contains(x, y)){
        if(winnerHalfTwo == 0){
            winnerHalfTwo = 2;
            drawFin2 = "4";
            drawThird2 = "2";
            emit sigPressWinner(3, true);
        }
        else if (winnerHalfTwo == 2){
            winnerHalfTwo = 0;
            drawFin2 = "";
            drawThird2 = "";
            emit sigPressWinner(3, false);
        }
    }
    else if(rectWinFin1.contains(x, y)){
        if(winnerFinal == 0){
            winnerFinal = 1;
            //drawFinal = drawFin1;
            emit sigPressWinner(4, true);
        }
        else if (winnerFinal == 1){
            winnerFinal = 0;
            //drawFinal = "";
            emit sigPressWinner(4, false);
        }
    }
    else if(rectWinFin2.contains(x, y)){
        if(winnerFinal == 0){
            winnerFinal = 2;
            //drawFinal = drawFin2;
            emit sigPressWinner(5, true);
        }
        else if (winnerFinal == 2){
            winnerFinal = 0;
            //drawFinal = "";
            emit sigPressWinner(5, false);
        }
    }
    else if(rectWinThird1.contains(x, y)){
        if(winnerThird == 0){
            winnerThird = 1;
            //drawThird = drawThird1;
            emit sigPressWinner(6, true);
        }
        else if (winnerThird == 1){
            winnerThird = 0;
            //drawThird = "";
            emit sigPressWinner(6, false);
        }
    }
    else if(rectWinThird2.contains(x, y)){
        if(winnerThird == 0){
            winnerThird = 2;
            //drawThird = drawThird2;
            emit sigPressWinner(7, true);
        }
        else if (winnerThird == 2){
            winnerThird = 0;
            //drawThird = "";
            emit sigPressWinner(7, false);
        }
    }

    if(winnerFinal == 1){
        drawFinal = drawFin1;
    }
    else if(winnerFinal == 2){
        drawFinal = drawFin2;
    }
    else{
        drawFinal = "";
    }

    if(winnerThird == 1)
        drawThird = drawThird1;
    else if(winnerFinal == 2)
        drawThird = drawThird2;
    else
        drawThird = "";

    /*Отправка на ковер*/
    if(rectHalf1.contains(x, y) || rectHalf3.contains(x, y) ||
        rectHalf2.contains(x, y) || rectHalf4.contains(x, y)){
        flagOnMatHalf = true;
        emit sigSendOnMat(0);
    }

    if(rectFin1.contains(x, y) || rectFin2.contains(x, y) ||
        rectThird1.contains(x, y) || rectThird2.contains(x, y)){
        flagOnMatFinal = true;
        emit sigSendOnMat(1);
    }
}

void ItemHalfAndFinalOne3::hoverMoveEvent(QGraphicsSceneHoverEvent* e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    if(e->pos().x() > 361 && e->pos().x() < 399 && e->pos().y() > 0 && e->pos().y() < 40){
        flagHoverWin1 = true;
        flagHoverWin2 = false;
        flagHoverWin3 = false;
        flagHoverWin4 = false;
        flagHoverWinHalf1 = false;
        flagHoverWinHalf2 = false;
        flagHoverWinThird1 = false;
        flagHoverWinThird2 = false;
    }
    else if(e->pos().x() > 361 && e->pos().x() < 399 && e->pos().y() > 80 && e->pos().y() < 120){
        flagHoverWin1 = false;
        flagHoverWin2 = true;
        flagHoverWin3 = false;
        flagHoverWin4 = false;
        flagHoverWinHalf1 = false;
        flagHoverWinHalf2 = false;
        flagHoverWinThird1 = false;
        flagHoverWinThird2 = false;
    }
    else if(e->pos().x() > 361 && e->pos().x() < 399 && e->pos().y() > 160 && e->pos().y() < 200){
        flagHoverWin1 = false;
        flagHoverWin2 = false;
        flagHoverWin3 = true;
        flagHoverWin4 = false;
        flagHoverWinHalf1 = false;
        flagHoverWinHalf2 = false;
        flagHoverWinThird1 = false;
        flagHoverWinThird2 = false;
    }
    else if(e->pos().x() > 361 && e->pos().x() < 399 && e->pos().y() > 240 && e->pos().y() < 280){
        flagHoverWin1 = false;
        flagHoverWin2 = false;
        flagHoverWin3 = false;
        flagHoverWin4 = true;
        flagHoverWinHalf1 = false;
        flagHoverWinHalf2 = false;
        flagHoverWinThird1 = false;
        flagHoverWinThird2 = false;
    }
    else if(e->pos().x() > 520 && e->pos().x() < 560 && e->pos().y() > 40 && e->pos().y() < 80){
        flagHoverWin1 = false;
        flagHoverWin2 = false;
        flagHoverWin3 = false;
        flagHoverWin4 = false;
        flagHoverWinHalf1 = true;
        flagHoverWinHalf2 = false;
        flagHoverWinThird1 = false;
        flagHoverWinThird2 = false;
    }
    else if(e->pos().x() > 520 && e->pos().x() < 560 && e->pos().y() > 200 && e->pos().y() < 240){
        flagHoverWin1 = false;
        flagHoverWin2 = false;
        flagHoverWin3 = false;
        flagHoverWin4 = false;
        flagHoverWinHalf1 = false;
        flagHoverWinHalf2 = true;
        flagHoverWinThird1 = false;
        flagHoverWinThird2 = false;
    }
    else if(e->pos().x() > 520 && e->pos().x() < 560 && e->pos().y() > 320 && e->pos().y() < 360){
        flagHoverWin1 = false;
        flagHoverWin2 = false;
        flagHoverWin3 = false;
        flagHoverWin4 = false;
        flagHoverWinHalf1 = false;
        flagHoverWinHalf2 = false;
        flagHoverWinThird1 = true;
        flagHoverWinThird2 = false;
    }
    else if(e->pos().x() > 520 && e->pos().x() < 560 && e->pos().y() > 400 && e->pos().y() < 440){
        flagHoverWin1 = false;
        flagHoverWin2 = false;
        flagHoverWin3 = false;
        flagHoverWin4 = false;
        flagHoverWinHalf1 = false;
        flagHoverWinHalf2 = false;
        flagHoverWinThird1 = false;
        flagHoverWinThird2 = true;
    }
    else{
        flagHoverWin1 = false;
        flagHoverWin2 = false;
        flagHoverWin3 = false;
        flagHoverWin4 = false;
        flagHoverWinHalf1 = false;
        flagHoverWinHalf2 = false;
        flagHoverWinThird1 = false;
        flagHoverWinThird2 = false;
    }

    if(rectHalf1.contains(x, y) || rectHalf3.contains(x, y) ||
        rectHalf2.contains(x, y) || rectHalf4.contains(x, y)){
        flagHoverHalf = true;
    }
    else{
        flagHoverHalf = false;
    }

    if(rectFin1.contains(x, y) || rectFin2.contains(x, y) ||
        rectThird1.contains(x, y) || rectThird2.contains(x, y)){
        flagHoverFinal = true;
    }
    else{
        flagHoverFinal = false;
    }

    update();
}
