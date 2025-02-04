#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "competitionsystem.h"
#include "database.h"
#include "mainwindow.h"
#include "qobject.h"
#include "addingathletes.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QObject* parent = nullptr);
    ~Controller();

public slots:
    void createCompetition(void);
    void openCompetition(void);
    void addAthletes(void);

private:
    AddingAthletes* add;
    DataBase* base;
    QList<CompetitionSystem*> lSystem;
    QString currentBase;
    MainWindow* main_window;

signals:
    ///////////////////////////////////////////////////////////
    /// \brief sigCompetition                               ///
    /// Сигнал при создании, открытии соревнований          ///
    /// и при добавлении спортсменов.                       ///
    /// Параметр - true, если кнопка добавления спортсменов ///
    /// должна быть активной                                ///
    ///////////////////////////////////////////////////////////
    void sigCompetition(QString);
};

#endif // CONTROLLER_H
