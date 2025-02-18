#ifndef MATSSTATUS_H
#define MATSSTATUS_H

#include "ledwidget.h"
#include "qlabel.h"
#include <QWidget>

class MatsStatus : public QWidget
{
    Q_OBJECT
public:
    MatsStatus(QWidget* parent = nullptr);

private:
    QPixmap pixClose;
    QPixmap pixCloseRed;
    QPixmap pixOpen;
    QPixmap pixOpenRed;

    QLabel* lblMat1;
    QLabel* lblMat1Sending;
    QLabel* lblMat1Recieving;

    QLabel* lblMat2;
    QLabel* lblMat2Sending;
    QLabel* lblMat2Recieving;

    QLabel* lblMat3;
    QLabel* lblMat3Sending;
    QLabel* lblMat3Recieving;

    LEDWidget* led1;
    LEDWidget* led2;
    LEDWidget* led3;

};

#endif // MATSSTATUS_H
