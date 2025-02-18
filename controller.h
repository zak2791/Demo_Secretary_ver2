#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "categoryonmat.h"
#include "competitionsystem.h"
#include "database.h"
#include "qobject.h"
//#include "addingathletes.h"

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
    //AddingAthletes* add;
    DataBase* base;
    QList<CompetitionSystem*> lSystem;
    QList<CategoryOnMat*> lCategoryOnMat1;
    QList<CategoryOnMat*> lCategoryOnMat2;
    QList<CategoryOnMat*> lCategoryOnMat3;
    QString currentBase;
    QObject* p;

private slots:
    void sendOnMat(int, int, int, QString, QString, QString, QVariant);
    void removeCategoryFromMat(int);

signals:
    ///////////////////////////////////////////////////////////
    /// \brief sigCompetition                               ///
    /// Сигнал при создании, открытии соревнований          ///
    /// и при добавлении спортсменов.                       ///
    /// Параметр - true, если кнопка добавления спортсменов ///
    /// должна быть активной                                ///
    ///////////////////////////////////////////////////////////
    void sigCompetition(QString, bool);

    void sigSetControlPanel(QList<std::tuple<int, QString, QString, QString>>);

    void sigIsertCategoryOnMat(CategoryOnMat*);
    void sigIsertCategoryOnMatFromBase(int, CategoryOnMat*);
    void sigClearMats(void);
    void sigRemoveCategoryFromMat(int/*id*/, int/*mat*/);
    void sigCancelSendOnMat(int, int);
    void sigRemovePanel(void);
};

#endif // CONTROLLER_H
