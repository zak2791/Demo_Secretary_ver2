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
    bool createBase(QString);           //создаёт базу данных
    bool createBaseOnMat(QString);      //создаёт базу данных для переноса на компьютер на ковре
    QList<std::tuple<int,               //id - идентификатор весовой категории
                    int,                //id_system - идентификатор системы проведения соревнований
                    int,                //status -
                    QList<athlete>,     //athletes - список спортсменов
                    QString,            //data - оценки, места и т. д.
                    QString,            //category - мужчины, женщины, ...
                    QString,            //age - возраст
                    QString             //weight - вес
                            >> getCategories(QString);   //открытие соревнования (чтение всех категорий)

    QList<std::tuple<int,                //id
                     int,                //id_category
                     int,                //id_system
                     int,                //mode - режим: первый круг, полуфинал, финал, ...
                     int,                //mat - номер ковра
                     QString,            //category
                     QString,            //age
                     QString,            //weight
                     QString             //data
                     >> getCategoriesOnMats(void);

    bool addCategories(QList<QStringList>);
    int createCategoryOnMat(int, int, int, int/*mat*/, QVariant);
    QList<int> deleteCategoryFromMat(int);

public slots:
    void writeData(int,                         //id категории
                   QString                      //данные
                   );



private:
    QSqlDatabase db;
    QSqlQuery* query;

    void writeCommonPlace(int, QString);        //запись места в общем круге 

};

#endif // DATABASE_H
