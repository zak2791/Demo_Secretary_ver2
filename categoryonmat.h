#ifndef CATEGORYONMAT_H
#define CATEGORYONMAT_H

#include "ledwidget.h"
#include "qlabel.h"
#include "qwidget.h"

class CategoryOnMat : public QFrame
{
    Q_OBJECT
public:
    CategoryOnMat(int, int, int, int, int, QString, QString, QString, QString, QWidget* parent = nullptr);
    int getId(void){return id;}
    int getStatus(void){return status;}
    void setStatus(int);
    QString getDataToSend(void);

private:
    int id;
    int id_category;
    int id_system;
    int mode;
    int status;    // 0 - исходный, 1  - данные на ковер доставлены, 2 - в работе
    QString sCategory;
    QString sAge;
    QString sWeight;
    QLabel* lblCategory;
    QLabel* lblAge;
    QLabel* lblWeight;
    QLabel* lblInfo;
    QString data;
    LEDWidget* LedDeliveredOnmat;
    LEDWidget* LedInWork;
    LEDWidget* LedChangeRead;

    virtual void mousePressEvent(QMouseEvent*);

signals:
    void sigRemoveFromMat(int);
    void sigClick(QString, QString, QString);
    void sigSendData(void);\

};

#endif // CATEGORYONMAT_H
