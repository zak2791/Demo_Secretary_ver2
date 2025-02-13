#include "controller.h"
#include "qdebug.h"
#include "jsonconverter.h"

#include "system_0.h"
#include "addcompetition.h"

Controller::Controller(QObject* parent) : QObject(parent) {
    add = new AddingAthletes;
    base = new DataBase;
    connect(this, &Controller::sigAddCategoryOnMat, base, &DataBase::createCategoryOnMat);
}

Controller::~Controller()
{
    delete add;
    delete base;
    foreach (auto each, lSystem)
        delete each;
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

void Controller::openCompetition(QString name)
{
    if(name != "")
        currentBase = name + ".db";
    foreach (auto each, lSystem)
        delete each;
    lSystem.clear();
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

        if(id_system == 0){
            CompetitionSystem* CS = new System_0(id, id_system, status, lA, data, category, age, weight);
            connect(CS, &CompetitionSystem::sigSaveData, base, &DataBase::writeData);
            connect(CS, &CompetitionSystem::sigSendOnMat, this, &Controller::sendOnMat);
            lSystem.append(CS);
        }

        lTpl.append(std::tuple(id, category, age, weight));

    }

    emit sigSetControlPanel(lTpl);
}

void Controller::addAthletes()
{
    connect(add, &AddingAthletes::sigAddAthletes, this, [this](QList<QStringList> l){
        base->addCategories(l);
        openCompetition();
        emit sigCompetition("");
    });

    add->show();

}

void Controller::sendOnMat(int id, int id_system, int mode , QString category, QString age, QString weight, QVariant data)
{
    int mat = emit sigRequestMat();

    int id_onMat = emit sigAddCategoryOnMat(id, id_system, mode, mat, data);
    CategoryOnMat* cat = new CategoryOnMat(id_onMat, id, id_system, mode, category, age, weight, data);
    lCategoryOnMat1.append(cat);
    emit sigIsertCategoryOnMat(cat);
    qDebug()<<"id_onMat = "<<id_onMat;
}

CompetitionSystem *Controller::getCategory(int id)
{
    foreach(auto each, lSystem)
        if(each->getId() == id)
            return each;
    return nullptr;
}

