#include "controller.h"
#include "qdebug.h"
#include "jsonconverter.h"

#include "system_0.h"
#include "addcompetition.h"

Controller::Controller(QObject* parent) : QObject(parent) {
    add = new AddingAthletes;
    base = new DataBase;
    main_window = static_cast<MainWindow*>(parent);
}

Controller::~Controller()
{
    delete add;
    delete base;
}

void Controller::createCompetition()
{
    AddCompetition* add = new AddCompetition();
    QString base_name;
    connect(add, &AddCompetition::sigNewBase, [&base_name](QString name){base_name = name;});
    int ret = add->exec();
    if(ret == 1){
        if(base->createBase(base_name)){
            currentBase = base_name;
            emit sigCompetition(base_name);
        }
    }
}

void Controller::openCompetition()
{
    foreach (auto each, lSystem)
        delete each;
    QList<std::tuple<int, QString, QString, QString>> lTpl;
    QList<std::tuple<int, int, int, QList<athlete>, QString, QString, QString, QString>> tpl = base->openBase(currentBase);
    foreach(auto each, tpl){
        int id = std::get<0>(each);
        int id_system = std::get<1>(each);
        int status = std::get<2>(each);
        QList<athlete> lA =  std::get<3>(each);
        QVariant data = JsonConverter::jsonToQVariant(id_system, std::get<4>(each));
        QString category = std::get<5>(each);
        QString age = std::get<6>(each);
        QString weight = std::get<7>(each);

        CompetitionSystem* CS = new System_0(id, id_system, status, lA, data, category, age, weight);

        lSystem.append(CS);

        lTpl.append(std::tuple(id, category, age, weight));

        qDebug()<<lSystem.count();
    }

    main_window->setControlPanel(lTpl);
}

void Controller::addAthletes()
{
    connect(add, &AddingAthletes::sigAddAthletes, this, [this](QList<QStringList> l){
        base->addCategories(l);
        openCompetition();
        emit sigCompetition("");
    });

    // connect(ui->aAdd, &QAction::triggered, this, [this](){
    //     qDebug()<<"aAdd";

    //     add->show();
    // });

    add->show();

}
