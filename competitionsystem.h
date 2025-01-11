#ifndef COMPETITIONSYSTEM_H
#define COMPETITIONSYSTEM_H

#include "qgraphicsscene.h"

class CompetitionSystem : public QGraphicsScene
{
    Q_OBJECT
public:
    CompetitionSystem();

public slots:
    ///////////////////////////////////////
    /// \brief setResult                ///
    /// установка результатов с ковра   ///
    ///////////////////////////////////////
    virtual void setResult(int,                 //id категории
                           int,                 //режим
                           QList<QString>       //список значений
                           ) = 0;

protected:
    int id;             //id категории
    int id_system;      //система проведения соревнований
    int sendingFlag;    //флаг ожидания отправки данных на ковер

protected slots:

    // virtual void saveData(int,                  //id категории
    //                       int,                  //режим
    //                       QList<QString>        //список значений
    //                       ) = 0;

    ///////////////////////////////////
    /// \brief sendOnMat            ///
    /// отправка данных на ковер    ///
    ///////////////////////////////////
    virtual void sendOnMat(int,                 //id категории
                           int,                 //режим
                           QList<QString>) = 0; //список значений

signals:
    void sigSendOnMat(int, int, QList<QString>);

    ///////////////////////////////////////////////////////////
    /// \brief sigSaveData Сигнал сохранения в базе данных  ///                                                            ///
    /// изменений при работе с пользовательским интерфейсом ///
    /// Режим:                                              ///
    /// 0 - сохранение места в общем круге                  ///
    ///////////////////////////////////////////////////////////
    void sigSaveData(int,               //id категории
                     int,               //id_system
                     int,               //режим
                     QList<QString>
                     );

};

#endif // COMPETITIONSYSTEM_H
