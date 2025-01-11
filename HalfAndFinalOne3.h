#ifndef HALFANDFINALONE3_H
#define HALFANDFINALONE3_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>

#include "main.h"

///////////////////////////////////////////////////////
/// \brief Полуфинал и финал с одним третьим местом ///
///////////////////////////////////////////////////////
class ItemHalfAndFinalOne3 : public QGraphicsObject
{
    Q_OBJECT
public:
    ItemHalfAndFinalOne3(QList<athlete> = {},   //список финалистов согласно порядка номеров жеребьёвки (1, 3, 2, 4)
                         QList<rates> = {},     //оценки (8 оценок - 4 полуфиналиста, 2 финалиста,
                                                //2 за третье место (порядок сверху вниз))
                         QList<int> = {},       //флаги победителей (0 - никто, 1 - верхний, 2 - нижний) полуфиналов, финала и за третье место
                         QList<bool> = {});     //флаги отправки на ковер полуфиналов и финалов (false - не отправлен, true - отправлен)

    void setAthletes(QList<athlete>);           //установить финалистов
    void setAthlete(int, athlete);              //установить финалиста
    void setRates(QList<rates>);                //установить оценки
    void cancelSendOnMat(int);                  //отмена отправки на ковер, 0 - отмена полуфиналов, 1 - отмена финалов

private:
    QRectF boundingRect(void) const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

    QList<QString> names;
    //QList<QString> names;
    QString name1 = "";
    QString name3 = "";
    QString name2 = "";
    QString name4 = "";

    QString team1 = "";
    QString team3 = "";
    QString team2 = "";
    QString team4 = "";

    QString range1 = "";
    QString range3 = "";
    QString range2 = "";
    QString range4 = "";

    //Оценки полуфинала, согласно номерам по жеребьевке
    QString rate1 = "";
    QString rate3 = "";
    QString rate2 = "";
    QString rate4 = "";
    QString addRate1 = "";
    QString addRate3 = "";
    QString addRate2 = "";
    QString addRate4 = "";

    //Оценки финала
    QString rateFin1 = "";
    QString rateFin2 = "";
    QString addRateFin1 = "";
    QString addRateFin2 = "";

    //Оценки за третье место
    QString rateThird1 = "";
    QString rateThird2 = "";
    QString addRateThird1 = "";
    QString addRateThird2 = "";

    /*Номера по жеребьёвке в сетке: */
    QString drawFin1 = "";      //первый финалист
    QString drawFin2 = "";      //второй финалист
    QString drawFinal = "";     //финалист
    QString drawThird1 = "";    //первый за третье место
    QString drawThird2 = "";    //второй за третье место
    QString drawThird = "";     //третье место

    QImage* win;
    QImage* win_hover;
    QImage* win_gray;
    QImage* win_gray_hover;

    /*Флаги наведения мыши на кнопки включения победителей: */
    bool flagHoverWin1 = false;
    bool flagHoverWin2 = false;
    bool flagHoverWin3 = false;
    bool flagHoverWin4 = false;
    bool flagHoverWinHalf1 = false;
    bool flagHoverWinHalf2 = false;
    bool flagHoverWinThird1 = false;
    bool flagHoverWinThird2 = false;

    /*Флаги отправки категорий на ковер*/
    bool flagOnMatHalf = false;
    //bool flagOnMatHalf2 = false;
    bool flagOnMatFinal = false;
    //bool flagOnMatThird = false;

    /*Флаги наведения мыши на номера жеребьевки полуфиналов и финалов*/
    bool flagHoverHalf  = false;
    bool flagHoverFinal = false;

    /*Победители в первом полуфинале: */
    int winnerHalfOne = 0;  //0 - нет, 1 - верхний (1), 2 - нижний (3)

    /*Победители во втором полуфинале: */
    int winnerHalfTwo = 0;  //0 - нет, 1 - верхний (2), 2 - нижний (4)

    /*Победители в финале: */
    int winnerFinal = 0;    //0 - нет, 1 - верхний, 2 - нижний

    /*Победители в бою за третье место: */
    int winnerThird = 0;    //0 - нет, 1 - верхний, 2 - нижний

    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;

    /*Области номеров жеребьевки полуфиналов*/
    QRect rectHalf1 = QRect(0,   0, 40, 40);
    QRect rectHalf3 = QRect(0,  80, 40, 40);
    QRect rectHalf2 = QRect(0, 160, 40, 40);
    QRect rectHalf4 = QRect(0, 240, 40, 40);

    /*Области номеров жеребьевки финалов*/
    QRect rectFin1   = QRect(400,  40,  40, 40);
    QRect rectFin2   = QRect(400, 200,  40, 40);
    QRect rectThird1 = QRect(400, 320,  40, 40);
    QRect rectThird2 = QRect(400, 400,  40, 40);

    /*Области кнопок выбора победителей жеребьевки финалов*/
    QRect rectWinHalf1 = QRect(360,   0, 40, 40);
    QRect rectWinHalf3 = QRect(360,  80, 40, 40);
    QRect rectWinHalf2 = QRect(360, 160, 40, 40);
    QRect rectWinHalf4 = QRect(360, 240, 40, 40);

    QRect rectWinFin1   = QRect(520, 40, 40, 40);
    QRect rectWinFin2   = QRect(520, 200, 40, 40);

    QRect rectWinThird1 = QRect(520, 320, 40, 40);
    QRect rectWinThird2 = QRect(520, 400, 40, 40);

signals:
    ///////////////////////////////////////////////
    /// \  sigPressWinner                   ///
    ///Сигнал нажатия кнопки выбора победителя  ///
    /// Параметры:                              ///
    /// 1 - номер кнопки                        ///
    /// 2 - статус (нажата, отжата)             ///
    ///////////////////////////////////////////////
    void sigPressWinner(int, bool);

    ///////////////////////////////////
    /// \brief sigSendOnMat         ///
    /// Сигнал отправки на ковер.   ///
    /// Параметр:                   ///
    /// 0 - полуфиналы              ///
    /// 1 - финалы                  ///
    ///////////////////////////////////
    void sigSendOnMat(int);

};

#endif // HALFANDFINALONE3_H
