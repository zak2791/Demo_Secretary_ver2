#include "controller.h"
#include "mainwindow.h"
#include "qdebug.h"
#include "jsonconverter.h"

#include "qmessagebox.h"
#include "system_0.h"
#include "addcompetition.h"

Controller::Controller(QObject* parent) : QObject(parent) {
    p = parent;
    add = new AddingAthletes;
    base = new DataBase;
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
            connect(this, &Controller::sigCancelSendOnMat, CS, &CompetitionSystem::cancelSendOnMat);
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
    int mat = static_cast<MainWindow*>(p)->getMat();
    int id_onMat = base->createCategoryOnMat(id, id_system, mode, mat, data);
    CategoryOnMat* cat = new CategoryOnMat(id_onMat, id, id_system, mode, category, age, weight, data);
    connect(cat, &CategoryOnMat::sigRemoveFromMat, this, &Controller::removeCategoryFromMat);

    if(mat == 0)
        lCategoryOnMat1.append(cat);
    else if(mat == 1)
        lCategoryOnMat2.append(cat);
    else
        lCategoryOnMat3.append(cat);
    emit sigIsertCategoryOnMat(cat);
}

void Controller::removeCategoryFromMat(int id)
{
    QMessageBox msgBox;
    QList<int> lI = base->deleteCategoryFromMat(id);
    qDebug()<<"lI.count() = "<<lI.count()<<lI;
    if(lI.count() == 2)
        emit sigCancelSendOnMat(lI.at(0), lI.at(1));
    else{
        msgBox.setText("Ошибка отмены отправки на ковёр");
        msgBox.exec();
    }
    int mat = static_cast<MainWindow*>(p)->getMat();
    QList<CategoryOnMat*> list;
    if(mat == 0)
        list = lCategoryOnMat1;
    else if(mat == 1)
        list = lCategoryOnMat2;
    else
        list = lCategoryOnMat3;
    for(int i = 0; i <  list.count(); i++){
        if(list.at(i)->getId() == id){
            delete list[i];
            list.removeAt(i);
            emit sigRemoveCategoryFromMat(id, mat);
            break;
        }
    }

}

CompetitionSystem *Controller::getCategory(int id)
{
    foreach(auto each, lSystem)
    if(each->getId() == id)
        return each;
    return nullptr;
}

