#ifndef DATABASE_H
#define DATABASE_H

#include "main.h"
#include <QtSql>

class DataBase : public QObject
{
    Q_OBJECT
public:
    DataBase();
    ~DataBase();
    bool createBase(QString);
    bool createBaseOnMat(QString);
    QList<std::tuple<int,
               int,
               int,
               QList<athlete>,
               QString,
               QString,
               QString,
               QString
                     >> openBase(QString);
    bool addCategories(QList<QStringList>);

private:
    QSqlDatabase db;
    QSqlQuery* query;

};

#endif // DATABASE_H
