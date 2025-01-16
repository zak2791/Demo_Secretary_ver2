#ifndef SYSTEM_0_H
#define SYSTEM_0_H

#include "system_0_final.h"
#include "competitionsystem.h"
#include "system_0_common.h"

///////////////////////////////////////////////////////////////////////////
/// \brief The CommonRoundHalfFinalTwoThird class                       ///
///Система проведения - общий круг, полуфинал, финал и 2 третьих места, ///
///код системы проведения - 0                                           ///
///////////////////////////////////////////////////////////////////////////
class System_0 : public CompetitionSystem
{
    Q_OBJECT
public:
    System_0(int,
             int,
             QList<athlete>,
             QVariant);

public slots:
    virtual void cancelSendOnMat(int,       //id категории
                                 int        //режим
                                 );

    virtual void setRates(int,              //id категории
                          int,              //режим
                          QList<rates>      //
                          );

private slots:
    void savePlace(//int,     //id спортсмена
                   //QString  //место
                    QList<athlete>
                   );

private:
    System_0_Common* commonRoundItem;
    System_0_Final* finalItem;


    //virtual void sendOnMat(int, int, QList<QString>);
    //QList<athlete> lAthlete;
};

#endif // SYSTEM_0_H
