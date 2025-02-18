#ifndef CATEGORYONMAT_H
#define CATEGORYONMAT_H

#include "qlabel.h"
#include "qwidget.h"

class CategoryOnMat : public QFrame
{
    Q_OBJECT
public:
    CategoryOnMat(int, int, int, int, QString, QString, QString, QVariant, QWidget* parent = nullptr);
    int getId(void){return id;}

private:
    int id;
    int id_category;
    int id_system;
    int mode;
    QString sCategory;
    QString sAge;
    QString sWeight;
    QLabel* lblCategory;
    QLabel* lblAge;
    QLabel* lblWeight;
    QLabel* lblInfo;
    QVariant vData;

    virtual void mousePressEvent(QMouseEvent*);

signals:
    void sigRemoveFromMat(int);
    void sigClick(QString, QString, QString);
};

#endif // CATEGORYONMAT_H
