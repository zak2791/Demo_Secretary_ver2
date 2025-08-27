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
                      int,
                      QList<athlete>,
                      QString,
                      QString c,
                      QString a,
                      QString w);

    int getId(void){return id;}

private slots:
    virtual void sendOnMat(int, QString) = 0;

public slots:



    virtual void cancelSendOnMat(int,       //id категории
                                 int       //режим
                                 ) = 0;

    // ///////////////////////////////////////
    // /// \brief setRates                ///
    // /// установка результатов с ковра   ///
    // ///////////////////////////////////////
    virtual void setRates(int,              //id категории
                          int,              //режим
                          QVariant           //оценки
                          ) = 0;



protected:
    int id;                     //id категории
    int id_system;              //система проведения соревнований
    int status;
    //int sendingFlag;          //флаг ожидания отправки данных на ковер
    QList<athlete> lAthlete;    //
    QString data;              //
    QString category;
    QString age;
    QString weight;


signals:
    void sigSendOnMat(int,               //id
                      int,               //id_system
                      int,               //mode
                      QString,           //категория
                      QString,           //возраст
                      QString,           //вес
                      QString            //data
                      );

    ///////////////////////////////////////////////////////////
    /// \brief sigSaveData Сигнал сохранения в базе данных  ///                                                            ///
    /// изменений при работе с пользовательским интерфейсом ///
    /// Режим:                                              ///
    /// 0 - сохранение места в общем круге                  ///
    ///////////////////////////////////////////////////////////
    void sigSaveData(int,               //id категории
                     QString            //данные для отправки
                     );




};

#endif // COMPETITIONSYSTEM_H
