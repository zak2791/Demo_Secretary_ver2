#ifndef SYSTEM_0_H
#define SYSTEM_0_H

#include "HalfAndFinalOne3.h"
#include "competitionsystem.h"
#include "firstround.h"

///////////////////////////////////////////////////////////////////////////
/// \brief The CommonRoundHalfFinalTwoThird class                       ///
///Система проведения - общий круг, полуфинал, финал и 2 третьих места, ///
///код системы проведения - 0                                           ///
///////////////////////////////////////////////////////////////////////////
class CommonRoundHalfFinalTwoThird : public CompetitionSystem
{
    Q_OBJECT
public:
    CommonRoundHalfFinalTwoThird(int, QList<athlete1round>);

public slots:
    virtual void setResult(int, int, QList<QString>);

private slots:
    void savePlace(int,     //id спортсмена
                   QString  //место
                   );

private:
    FirstRound* commonRoundItem;
    ItemHalfAndFinalOne3* finalItem;


    virtual void sendOnMat(int, int, QList<QString>);
    QList<athlete1round> lAthlete;
};

#endif // SYSTEM_0_H
