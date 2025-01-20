#ifndef COMPETITIONSYSTEM_H
#define COMPETITIONSYSTEM_H

#include "qgraphicsscene.h"
#include "main.h"

class CompetitionSystem : public QGraphicsScene
{
    Q_OBJECT
public:
    CompetitionSystem(int,
                      int,
                      QList<athlete>,
                      QVariant,
                      QString c,
                      QString a,
                      QString w);
    //bool isCategory(QString c, QString a, QString w){return c == category && a == age && w == weight;}

public slots:

    // virtual void setResult(int,                 //id категории
    //                        int,                 //режим
    //                        QList<QString>       //список значений
    //                        ) = 0;

    virtual void cancelSendOnMat(int,       //id категории
                                 int       //режим
                                 //QString,   //категория
                                 //QString,   //возраст
                                 //QString    //вес
                                 ) = 0;

    ///////////////////////////////////////
    /// \brief setRates                ///
    /// установка результатов с ковра   ///
    ///////////////////////////////////////
    virtual void setRates(int,              //id категории
                          int,              //режим
                          QList<rates>      //оценки
                          ) = 0;

protected:
    int id;                     //id категории
    int id_system;              //система проведения соревнований
    //int sendingFlag;          //флаг ожидания отправки данных на ковер
    QList<athlete> lAthlete;    //
    QVariant data;              //
    QString category;
    QString age;
    QString weight;

signals:
    void sigSendOnMat(int,
                      int,
                      int,
                      QVariant
                      );

    ///////////////////////////////////////////////////////////
    /// \brief sigSaveData Сигнал сохранения в базе данных  ///                                                            ///
    /// изменений при работе с пользовательским интерфейсом ///
    /// Режим:                                              ///
    /// 0 - сохранение места в общем круге                  ///
    ///////////////////////////////////////////////////////////
    void sigSaveData(int,               //id категории
                     int,               //id_system ???
                     int,               //режим
                     QVariant           //данные для отправки
                     );




};

#endif // COMPETITIONSYSTEM_H
