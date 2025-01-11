#ifndef MAIN_H
#define MAIN_H

#include <QString>

struct athlete
{
    athlete(QString n, QString t, QString r) {name = n; team = t, range = r;}
    QString name;
    QString team;
    QString range;
};

struct rates
{
    rates(QString r, QString ar) {rate = r; addRate = ar;}
    QString rate;
    QString addRate;
};

struct athlete1round{
    athlete1round(QString n, QString t, QString rng, QString r, QString a,  QString p, int i)
    {name = n;
     team = t;
     range = rng;
     rate = r;
     addRate = a;
     place = p;
     id = i;
    }

    QString name;
    QString team;
    QString range;
    QString rate;
    QString addRate;
    QString place;
    int id;

    bool operator<(const athlete1round& obj){
        return place < obj.place;
    }
};

#endif // MAIN_H
