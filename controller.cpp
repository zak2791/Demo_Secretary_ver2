#include "controller.h"
#include "mainwindow.h"
#include "qdebug.h"
#include "jsonconverter.h"

#include "qmessagebox.h"
#include "system_0.h"
#include "addcompetition.h"
#include "addingathletes.h"

Controller::Controller(QObject* parent) : QObject(parent) {
    p = parent;
    //add = new AddingAthletes;
    base = new DataBase;
}

Controller::~Controller()
{
    //delete add;
    delete base;
    foreach (auto each, lSystem)
        delete each;
}

void Controller::createCompetition()
{
    AddCompetition* add = new AddCompetition();
    QString base_name;
    connect(add, &AddCompetition::sigNewBase, [&](QString name){
        base_name = name;
        foreach (auto each, lSystem)
            delete each;
        lSystem.clear();
        foreach (auto each, lCategoryOnMat1)
            delete each;
        lCategoryOnMat1.clear();

        foreach (auto each, lCategoryOnMat2)
            delete each;
        lCategoryOnMat2.clear();

        foreach (auto each, lCategoryOnMat3)
            delete each;
        lCategoryOnMat3.clear();
        emit sigClearMats();
    });
    int ret = add->exec();
    if(ret == 1){
        if(base->createBase(base_name)){
            currentBase = base_name;
            emit sigCompetition(base_name, true);
        }
    }

    emit sigRemovePanel();
}

void Controller::openCompetition(QString name)
{
    if(name != "")
        currentBase = name + ".db";
    ///////////////////////////
    /// заполняем категории ///
    ///////////////////////////
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

    /////////////////////////////////////
    /// заполняем категории на коврах ///
    /////////////////////////////////////
    foreach (auto each, lCategoryOnMat1)
        delete each;
    lCategoryOnMat1.clear();

    foreach (auto each, lCategoryOnMat2)
        delete each;
    lCategoryOnMat2.clear();

    foreach (auto each, lCategoryOnMat3)
        delete each;
    lCategoryOnMat3.clear();

    emit sigClearMats();

    QList<std::tuple<int, int, int, int, int, QString, QString, QString, QString>> lCatOnMat = base->readCategoryOnMats();
    foreach(auto each, lCatOnMat){
        int mat = std::get<4>(each);
        qDebug()<<"mat = "<<mat;
        CategoryOnMat* cat = new CategoryOnMat(std::get<0>(each),   //id_onMat
                                               std::get<1>(each),   //id
                                               std::get<2>(each),   //id_system
                                               std::get<3>(each),   //mode
                                               std::get<6>(each),   //category
                                               std::get<7>(each),   //age
                                               std::get<8>(each),   //weight
                                               std::get<5>(each)    //data
                                               );
        connect(cat, &CategoryOnMat::sigRemoveFromMat, this, &Controller::removeCategoryFromMat);
        connect(cat, &CategoryOnMat::sigClick, static_cast<MainWindow*>(p), &MainWindow::clickCategoryOnMat);
        if(mat == 0)
            lCategoryOnMat1.append(cat);
        else if(mat == 1)
            lCategoryOnMat2.append(cat);
        else
            lCategoryOnMat3.append(cat);
        emit sigIsertCategoryOnMatFromBase(mat, cat);
    }

    emit sigSetControlPanel(lTpl);
    if(lSystem.isEmpty())
        emit sigCompetition(currentBase, true);
    else
        emit sigCompetition(currentBase, false);
}

void Controller::addAthletes()
{
    AddingAthletes* add = new AddingAthletes;

    connect(add, &AddingAthletes::sigAddAthletes, this, [this](QList<QStringList> l){
        base->addCategories(l);
        openCompetition();
        //emit sigCompetition("");
    });

    add->show();

}

void Controller::sendOnMat(int id, int id_system, int mode , QString category, QString age, QString weight, QVariant data)
{
    int mat = static_cast<MainWindow*>(p)->getMat();
    int id_onMat = base->createCategoryOnMat(id, id_system, mode, mat, data);
    CategoryOnMat* cat = new CategoryOnMat(id_onMat, id, id_system, mode, category, age, weight, data);
    connect(cat, &CategoryOnMat::sigRemoveFromMat, this, &Controller::removeCategoryFromMat);
    connect(cat, &CategoryOnMat::sigClick, static_cast<MainWindow*>(p), &MainWindow::clickCategoryOnMat);
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
    if(lI.count() == 2)
        emit sigCancelSendOnMat(lI.at(0), lI.at(1));
    else{
        msgBox.setText("Ошибка отмены отправки на ковёр");
        msgBox.exec();
    }
    int mat = static_cast<MainWindow*>(p)->getMat();
    if(mat == 0){
        for(int i = 0; i <  lCategoryOnMat1.count(); i++){
            if(lCategoryOnMat1.at(i)->getId() == id){
                delete lCategoryOnMat1[i];
                lCategoryOnMat1.removeAt(i);
                emit sigRemoveCategoryFromMat(id, mat);
                break;
            }
        }
    }
    else if(mat == 1){
        for(int i = 0; i <  lCategoryOnMat2.count(); i++){
            if(lCategoryOnMat2.at(i)->getId() == id){
                delete lCategoryOnMat2[i];
                lCategoryOnMat2.removeAt(i);
                emit sigRemoveCategoryFromMat(id, mat);
                break;
            }
        }
    }
    else{
        for(int i = 0; i <  lCategoryOnMat3.count(); i++){
            if(lCategoryOnMat3.at(i)->getId() == id){
                delete lCategoryOnMat3[i];
                lCategoryOnMat3.removeAt(i);
                emit sigRemoveCategoryFromMat(id, mat);
                break;
            }
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

