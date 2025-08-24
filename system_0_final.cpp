#include "system_0_final.h"
#include "qjsonarray.h"
#include "qjsondocument.h"

#include <QPainter>

System_0_Final::System_0_Final(QList<athlete> aList,
                               QString data
                               ) {

    lAthlete = aList;
    setAthletes(data);

    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    data_final = doc.object()["FinalData"].toObject();
    // if(aList.count() == 4){
    //     athlete1 = aList.at(0);
    //     athlete3 = aList.at(3);
    //     athlete2 = aList.at(1);
    //     athlete4 = aList.at(2);
    // }
    //qDebug()<<athlete1.id;
    //data_final_0 = data;

    //победитель 1-го полуфинала
    if(data_final["WinnerHalf1"].toString() == "1"){
        drawFin1 = "1";
        drawThird1 = "3";
    }else if(data_final["WinnerHalf1"].toString() == "2"){
        drawFin1 = "3";
        drawThird1 = "1";
    }

    //победитель 2-го полуфинала
    if(data_final["WinnerHalf2"].toString() == "1"){
        drawFin2 = "2";
        drawThird2 = "4";
    }else if(data_final["WinnerHalf2"].toString() == "2"){
        drawFin2 = "4";
        drawThird2 = "2";
    }

    //победитель финала
    if(data_final["WinnerFinal"].toString() == "1"){
        drawFinal = drawFin1;
    }else if(data_final["WinnerFinal"].toString() == "2"){
        drawFinal = drawFin2;
    }

    //победитель за 3 место
    if(data_final["WinnerThird"].toString() == "1"){
        drawThird = drawThird1;
    }else if(data_final["WinnerThird"].toString() == "2"){
        drawThird = drawThird2;
    }

    //flagOnMatHalf  = data_final_0.flag_on_mat_half;
    //flagOnMatFinal = data_final_0.flag_on_mat_final;


    setAcceptHoverEvents(true);

    win              = new QImage(":/images/win.png");
    win_hover        = new QImage(":/images/win_hover.png");
    win_gray         = new QImage(":/images/win_gray.png");
    win_gray_hover   = new QImage(":/images/win_gray_hover.png");

}

QRectF System_0_Final::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(penWidth / 2 - 10, penWidth / 2 - 10,
                  680 + penWidth + 10, 440 + penWidth + 10);
}

void System_0_Final::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem*,
                           QWidget*)
{
    if(data_final["OnMatHalf"].toBool()){
        painter->fillRect(rectHalf1, "lightgreen");
        painter->fillRect(rectHalf3, "lightgreen");
        painter->fillRect(rectHalf2, "lightgreen");
        painter->fillRect(rectHalf4, "lightgreen");
    }
    else if(flagHoverHalf){
        painter->fillRect(rectHalf1, "lightgray");
        painter->fillRect(rectHalf3, "lightgray");
        painter->fillRect(rectHalf2, "lightgray");
        painter->fillRect(rectHalf4, "lightgray");
    }
    painter->drawRect(rectHalf1);
    painter->drawRect(rectHalf3);
    painter->drawRect(rectHalf2);
    painter->drawRect(rectHalf4);

    if(data_final["OnMatFinal"].toBool()){
        painter->fillRect(rectFin1,    "lightgreen");
        painter->fillRect(rectFin2,    "lightgreen");
        painter->fillRect(rectThird1, "lightgreen");
        painter->fillRect(rectThird2, "lightgreen");
    }
    else if(flagHoverFinal){
        painter->fillRect(rectFin1,    "lightgray");
        painter->fillRect(rectFin2,   "lightgray");
        painter->fillRect(rectThird1, "lightgray");
        painter->fillRect(rectThird2, "lightgray");
    }
    painter->drawRect(rectFin1);
    painter->drawRect(rectFin2);
    painter->drawRect(rectThird1);
    painter->drawRect(rectThird2);

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

    painter->drawText(QRect(40 + 3,   0, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, athlete1.name);
    painter->drawText(QRect(40 + 3,  80, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, athlete3.name);
    painter->drawText(QRect(40 + 3, 160, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, athlete2.name);
    painter->drawText(QRect(40 + 3, 240, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, athlete4.name);

    painter->drawText(QRect(140 + 3,   0, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, athlete1.team);
    painter->drawText(QRect(140 + 3,  80, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, athlete3.team);
    painter->drawText(QRect(140 + 3, 160, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, athlete2.team);
    painter->drawText(QRect(140 + 3, 240, 100, 40), Qt::AlignVCenter | Qt::AlignLeft, athlete4.team);

    painter->drawText(QRect(240,   0,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, athlete1.range);
    painter->drawText(QRect(240,  80,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, athlete3.range);
    painter->drawText(QRect(240, 160,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, athlete2.range);
    painter->drawText(QRect(240, 240,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, athlete4.range);

    painter->drawText(QRect(280,   0,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["Rate1"].toString());
    painter->drawText(QRect(280,  80,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["Rate2"].toString());
    painter->drawText(QRect(280, 160,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["Rate3"].toString());
    painter->drawText(QRect(280, 240,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["Rate4"].toString());

    painter->drawText(QRect(320,   0,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["AddRate1"].toString());
    painter->drawText(QRect(320,  80,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["AddRate2"].toString());
    painter->drawText(QRect(320, 160,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["AddRate3"].toString());
    painter->drawText(QRect(320, 240,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["AddRate4"].toString());

    painter->drawText(QRect(440,  40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["RateFinal1"].toString());
    painter->drawText(QRect(440, 200,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["RateFinal2"].toString());
    painter->drawText(QRect(440, 320,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["RateThird1"].toString());
    painter->drawText(QRect(440, 400,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["RateThird2"].toString());

    painter->drawText(QRect(480,  40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["AddRateFinal1"].toString());
    painter->drawText(QRect(480, 200,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["AddRateFinal2"].toString());
    painter->drawText(QRect(480, 320,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["AddRateThird1"].toString());
    painter->drawText(QRect(480, 400,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, data_final["AddRateThird2"].toString());

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
        if(data_final["WinnerHalf1"].toString() == "0")
            painter->drawImage(rectWinHalf1, *win_gray_hover);
        else if(data_final["WinnerHalf1"].toString() == "1")
            painter->drawImage(rectWinHalf1, *win_hover);
        else
            painter->drawImage(rectWinHalf1, *win_gray);
    }
    else{
        if(data_final["WinnerHalf1"].toString() == "1")
            painter->drawImage(rectWinHalf1, *win);
        else
            painter->drawImage(rectWinHalf1, *win_gray);
    }
    if(flagHoverWin2){
        if(data_final["WinnerHalf1"].toString() == "0")
            painter->drawImage(rectWinHalf3, *win_gray_hover);
        else if(data_final["WinnerHalf1"].toString() == "2")
            painter->drawImage(rectWinHalf3, *win_hover);
        else
            painter->drawImage(rectWinHalf3, *win_gray);
    }
    else{
        if(data_final["WinnerHalf1"].toString() == "2")
            painter->drawImage(rectWinHalf3, *win);
        else
            painter->drawImage(rectWinHalf3, *win_gray);
    }
    if(flagHoverWin3){
        if(data_final["WinnerHalf2"].toString() == "0")
            painter->drawImage(rectWinHalf2, *win_gray_hover);
        else if(data_final["WinnerHalf2"].toString() == "1")
            painter->drawImage(rectWinHalf2, *win_hover);
        else
            painter->drawImage(rectWinHalf2, *win_gray);
    }
    else{
        if(data_final["WinnerHalf2"].toString() == "1")
            painter->drawImage(rectWinHalf2, *win);
        else
            painter->drawImage(rectWinHalf2, *win_gray);
    }
    if(flagHoverWin4){
        if(data_final["WinnerHalf2"].toString() == "0")
            painter->drawImage(rectWinHalf4, *win_gray_hover);
        else if(data_final["WinnerHalf2"].toString() == "2")
            painter->drawImage(rectWinHalf4, *win_hover);
        else
            painter->drawImage(rectWinHalf4, *win_gray);
    }
    else{
        if(data_final["WinnerHalf2"].toString() == "2")
            painter->drawImage(rectWinHalf4, *win);
        else
            painter->drawImage(rectWinHalf4, *win_gray);
    }
    if(flagHoverWinHalf1){
        if(data_final["WinnerFinal"].toString() == "0")
            painter->drawImage(rectWinFin1, *win_gray_hover);
        else if(data_final["WinnerFinal"].toString() == "1")
            painter->drawImage(rectWinFin1, *win_hover);
        else
            painter->drawImage(rectWinFin1, *win_gray);
    }
    else{
        if(data_final["WinnerFinal"].toString() == "1")
            painter->drawImage(rectWinFin1, *win);
        else
            painter->drawImage(rectWinFin1, *win_gray);
    }
    if(flagHoverWinHalf2){
        if(data_final["WinnerFinal"].toString() == "0")
            painter->drawImage(rectWinFin2, *win_gray_hover);
        else if(data_final["WinnerFinal"].toString() == "2")
            painter->drawImage(rectWinFin2, *win_hover);
        else
            painter->drawImage(rectWinFin2, *win_gray);
    }
    else{
        if(data_final["WinnerFinal"].toString() == "2")
            painter->drawImage(rectWinFin2, *win);
        else
            painter->drawImage(rectWinFin2, *win_gray);
    }
    if(flagHoverWinThird1){
        if(data_final["WinnerThird"].toString() == "0")
            painter->drawImage(rectWinThird1, *win_gray_hover);
        else if(data_final["WinnerThird"].toString() == "1")
            painter->drawImage(rectWinThird1, *win_hover);
        else
            painter->drawImage(rectWinThird1, *win_gray);
    }
    else{
        if(data_final["WinnerThird"].toString() == "1")
            painter->drawImage(rectWinThird1, *win);
        else
            painter->drawImage(rectWinThird1, *win_gray);
    }
    if(flagHoverWinThird2){
        if(data_final["WinnerThird"].toString() == "0")
            painter->drawImage(rectWinThird2, *win_gray_hover);
        else if(data_final["WinnerThird"].toString() == "2")
            painter->drawImage(rectWinThird2, *win_hover);
        else
            painter->drawImage(rectWinThird2, *win_gray);
    }
    else{
        if(data_final["WinnerThird"].toString() == "2")
            painter->drawImage(rectWinThird2, *win);
        else
            painter->drawImage(rectWinThird2, *win_gray);
    }

}

void System_0_Final::setAthletes(QString str)
{
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject jObj = doc.object()["CommonData"].toObject();
    QJsonArray arrId = jObj["Id"].toArray();
    QJsonArray arrPlaces = jObj["Places"].toArray();
    athlete1 = athlete();
    athlete3 = athlete();
    athlete2 = athlete();
    athlete4 = athlete();
    for(int i = 0; i < arrPlaces.count(); i++){
        if(arrPlaces.at(i).toString() == "1"){
            int id = arrId.at(i).toInt();
            foreach(auto each, lAthlete)
                if(each.id == id)
                    athlete1 = each;
        }else if(arrPlaces.at(i).toString() == "2"){
            int id = arrId.at(i).toInt();
            foreach(auto each, lAthlete)
                if(each.id == id)
                    athlete3 = each;
        }else if(arrPlaces.at(i).toString() == "3"){
            int id = arrId.at(i).toInt();
            foreach(auto each, lAthlete)
                if(each.id == id)
                    athlete2 = each;
        }else if(arrPlaces.at(i).toString() == "4"){
            int id = arrId.at(i).toInt();
            foreach(auto each, lAthlete)
                if(each.id == id)
                    athlete4 = each;
        }
    }
    update();
}

void System_0_Final::setRates(int mode, QList<rates> rates)
{
    if(mode == 1){
        data_final["Rate1"] = rates.at(0).rate;
        data_final["Rate2"] = rates.at(1).rate;
        data_final["Rate3"] = rates.at(2).rate;
        data_final["Rate4"] = rates.at(3).rate;
        data_final["AddRate1"] = rates.at(0).add_rate;
        data_final["AddRate2"] = rates.at(1).add_rate;
        data_final["AddRate3"] = rates.at(2).add_rate;
        data_final["AddRate4"] = rates.at(3).add_rate;
    }
    else{
        data_final["RateFinal1"] = rates.at(0).rate;
        data_final["RateFinal2"] = rates.at(1).rate;
        data_final["RateThird1"] = rates.at(2).rate;
        data_final["RateThird2"] = rates.at(3).rate;
        data_final["AddRateFinal1"] = rates.at(0).add_rate;
        data_final["AddRateFinal2"] = rates.at(1).add_rate;
        data_final["AddRateThird1"] = rates.at(2).add_rate;
        data_final["AddRateThird2"] = rates.at(3).add_rate;
    }
    update();
}

void System_0_Final::cancelSendOnMat(int onmat)
{
    if(onmat == 0)
        data_final["OnMatHalf"]  = false;
    else
        data_final["OnMatFinal"] = false;
}

void System_0_Final::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    /*Выбор победителей*/
    if(rectWinHalf1.contains(x, y)){
        if(data_final["WinnerHalf1"].toString() == "0"){
            data_final["WinnerHalf1"] = "1";
            drawFin1 = "1";
            drawThird1 = "3";
            emit sigPressWinner(0, true);
        }
        else if (data_final["WinnerHalf1"].toString() == "1"){
            data_final["WinnerHalf1"] = "0";
            drawFin1 = "";
            drawThird1 = "";
            emit sigPressWinner(0, false);
        }
    }
    else if(rectWinHalf3.contains(x, y)){
        if(data_final["WinnerHalf1"].toString() == "0"){
            data_final["WinnerHalf1"] = "2";
            drawFin1 = "3";
            drawThird1 = "1";
            emit sigPressWinner(1, true);
        }
        else if (data_final["WinnerHalf1"].toString() == "2"){
            data_final["WinnerHalf1"] = "0";
            drawFin1 = "";
            drawThird1 = "";
            emit sigPressWinner(1, false);
        }
    }
    else if(rectWinHalf2.contains(x, y)){
        if(data_final["WinnerHalf2"].toString() == "0"){
            data_final["WinnerHalf2"] = "1";
            drawFin2 = "2";
            drawThird2 = "4";
            emit sigPressWinner(2, true);
        }
        else if (data_final["WinnerHalf2"].toString() == "1"){
            data_final["WinnerHalf2"] = "0";
            drawFin2 = "";
            drawThird2 = "";
            emit sigPressWinner(2, false);
        }
    }
    else if(rectWinHalf4.contains(x, y)){
        if(data_final["WinnerHalf2"].toString() == "0"){
            data_final["WinnerHalf2"] = "2";
            drawFin2 = "4";
            drawThird2 = "2";
            emit sigPressWinner(3, true);
        }
        else if (data_final["WinnerHalf2"].toString() == "2"){
            data_final["WinnerHalf2"] = 0;
            drawFin2 = "";
            drawThird2 = "";
            emit sigPressWinner(3, false);
        }
    }
    else if(rectWinFin1.contains(x, y)){
        if(data_final["WinnerFinal"].toString() == "0"){
            data_final["WinnerFinal"] = "1";
            //drawFinal = drawFin1;
            emit sigPressWinner(4, true);
        }
        else if (data_final["WinnerFinal"].toString() == "1"){
            data_final["WinnerFinal"] = "0";
            //drawFinal = "";
            emit sigPressWinner(4, false);
        }
    }
    else if(rectWinFin2.contains(x, y)){
        if(data_final["WinnerFinal"].toString() == "0"){
            data_final["WinnerFinal"] = "2";
            //drawFinal = drawFin2;
            emit sigPressWinner(5, true);
        }
        else if (data_final["WinnerFinal"].toString() == "2"){
            data_final["WinnerFinal"] = "0";
            //drawFinal = "";
            emit sigPressWinner(5, false);
        }
    }
    else if(rectWinThird1.contains(x, y)){
        if(data_final["WinnerThird"].toString() == "0"){
            data_final["WinnerThird"] = "1";
            //drawThird = drawThird1;
            emit sigPressWinner(6, true);
        }
        else if (data_final["WinnerThird"].toString() == "1"){
            data_final["WinnerThird"] = "0";
            //drawThird = "";
            emit sigPressWinner(6, false);
        }
    }
    else if(rectWinThird2.contains(x, y)){
        if(data_final["WinnerThird"].toString() == "0"){
            data_final["WinnerThird"] = "2";
            //drawThird = drawThird2;
            emit sigPressWinner(7, true);
        }
        else if (data_final["WinnerThird"].toString() == "2"){
            data_final["WinnerThird"] = "0";
            //drawThird = "";
            emit sigPressWinner(7, false);
        }
    }

    if(data_final["WinnerFinal"].toString() == "1"){
        drawFinal = drawFin1;
    }
    else if(data_final["WinnerFinal"].toString() == "2"){
        drawFinal = drawFin2;
    }
    else{
        drawFinal = "";
    }

    if(data_final["WinnerThird"].toString() == "1")
        drawThird = drawThird1;
    else if(data_final["WinnerThird"].toString() == "2")
        drawThird = drawThird2;
    else
        drawThird = "";

    /*Отправка на ковер*/
    if(rectHalf1.contains(x, y) || rectHalf3.contains(x, y) ||
        rectHalf2.contains(x, y) || rectHalf4.contains(x, y)){
        data_final["OnMatHalf"] = true;
        QVariant data;
        QJsonArray jArr;
        QJsonObject jObj;
        for(int i = 0; i < 4; i++){
            if(data_final["WinnerHalf1"].toString() == "1"){
                jObj.insert("id", athlete1.id);
                jObj.insert("name", athlete1.name);
                jObj.insert("team", athlete1.team);
                jObj.insert("range", athlete1.range);
            }
            else if(data_final["WinnerHalf1"].toString() == "1"){
                jObj.insert("id", athlete3.id);
                jObj.insert("name", athlete3.name);
                jObj.insert("team", athlete3.team);
                jObj.insert("range", athlete3.range);
            }
            else{
                jObj.insert("id", -1);
                jObj.insert("name", "");
                jObj.insert("team", "");
                jObj.insert("range", "");
            }
        }
        // jObj.insert("id", lAthletes.at(i).id);
        // jObj.insert("name", lAthletes.at(i).name);
        // jObj.insert("team", lAthletes.at(i).team);
        // jObj.insert("range", lAthletes.at(i).range);
        emit sigOnMAt(1, data);
    }

    if(rectFin1.contains(x, y) || rectFin2.contains(x, y) ||
        rectThird1.contains(x, y) || rectThird2.contains(x, y)){
        data_final["OnMatFinal"] = true;
        QVariant data;
        emit sigOnMAt(2, data);
    }
}

void System_0_Final::hoverMoveEvent(QGraphicsSceneHoverEvent* e)
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
