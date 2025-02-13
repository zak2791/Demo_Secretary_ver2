#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "categoryonmat.h"
#include "competitionsystem.h"
#include "database.h"
#include "qobject.h"
#include "addingathletes.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QObject* parent = nullptr);
    ~Controller();
    CompetitionSystem* getCategory(int);

public slots:
    void createCompetition(void);
    void openCompetition(QString name = "");
    void addAthletes(void);


private:
    AddingAthletes* add;
    DataBase* base;
    QList<CompetitionSystem*> lSystem;
    QList<CategoryOnMat*> lCategoryOnMat1;
    QList<CategoryOnMat*> lCategoryOnMat2;
    QList<CategoryOnMat*> lCategoryOnMat3;
    QString currentBase;

private slots:
    void sendOnMat(int, int, int, QString, QString, QString, QVariant);

signals:
    ///////////////////////////////////////////////////////////
    /// \brief sigCompetition                               ///
    /// Сигнал при создании, открытии соревнований          ///
    /// и при добавлении спортсменов.                       ///
    /// Параметр - true, если кнопка добавления спортсменов ///
    /// должна быть активной                                ///
    ///////////////////////////////////////////////////////////
    void sigCompetition(QString);

    void sigSetControlPanel(QList<std::tuple<int, QString, QString, QString>>);

    //void sigCategory(CompetitionSystem*);
    int sigAddCategoryOnMat(int,        //id категории
                            int,        //id_system
                            int,        //mode
                            int,        //mat
                            QVariant    //data
                            );

    int sigRequestMat(void);
    void sigIsertCategoryOnMat(CategoryOnMat*);

};

#endif // CONTROLLER_H
