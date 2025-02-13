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
    int createCategoryOnMat(int, int, int, int/*mat*/, QVariant);
    QList<int> deleteCategoryFromMat(int);

public slots:
    void writeData(int,                         //id категории
                   int,                         //id system
                   int,                         //mode (0-сохранение места общего круга)
                   QVariant                     //данные
                   );



private:
    QSqlDatabase db;
    QSqlQuery* query;

    void writeCommonPlace(int, QString);        //запись места в общем круге

};

#endif // DATABASE_H
