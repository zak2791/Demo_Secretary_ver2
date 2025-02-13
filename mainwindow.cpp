#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar = new QStatusBar(this);
    statusBar->addWidget(&lblStatus);
    setStatusBar(statusBar);

    listWidgetMat1 = ui->lwMat1;
    listWidgetMat2 = ui->lwMat2;
    listWidgetMat3 = ui->lwMat3;

    fillMenuLastCompetitions();

    QAction* actAdd = ui->aAdd;
    controller = new Controller(this);
    connect(ui->aCreate,    &QAction::triggered,         controller, &::Controller::createCompetition);
    connect(ui->aAdd,       &QAction::triggered,         controller, &::Controller::addAthletes);

    connect(controller,     &Controller:: sigCompetition, [actAdd, this](QString s) {
        if(s == "")
            actAdd->setEnabled(false);
        else{
            actAdd->setEnabled(true);
            lblStatus.setText(s.left(s.lastIndexOf(".")).replace("_", " "));
        }
    });

    connect(controller, SIGNAL(sigSetControlPanel(QList<std::tuple<int,QString,QString,QString> >)), this,
            SLOT(setControlPanel(QList<std::tuple<int,QString,QString,QString> >)));

    connect(controller, &Controller::sigIsertCategoryOnMat, this, &MainWindow::insertCategoryOnMat);

    connect(controller, &Controller::sigRemoveCategoryFromMat, [this](int id, int mat){
        QListWidget* lWidget;
        if(mat == 0){
            lWidget = listWidgetMat1;
        }
        else if(mat == 1){
            lWidget = listWidgetMat2;
        }
        else{
            lWidget = listWidgetMat3;
        }
        for(int i = 0; i < lWidget->count(); i++){
            if(lWidget->item(i)->data(Qt::UserRole) == id){
                delete lWidget->item(i);
            }
        }
    ;});

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getMat()
{
    if(ui->tabMats->currentWidget()->objectName() == "tabMat1")
        return 0;
    else if(ui->tabMats->currentWidget()->objectName() == "tabMat2")
        return 1;
    else
        return 2;
}

void MainWindow::setControlPanel(QList<std::tuple<int, QString, QString, QString>> list)
{
    panel = findChild<CategoryControlPanel*>();
    if(panel != nullptr){
        ui->verticalLayout->removeWidget(panel);
    }
    delete panel;

    panel = new CategoryControlPanel(list);
    ui->verticalLayout->insertWidget(0, panel);
    connect(panel, SIGNAL(sigChoosingCategory(int)), this, SLOT(setCategory(int)));
    setCategory(panel->getId());
}

void MainWindow::setCategory(int id)
{
    ui->gViewMain->setScene(controller->getCategory(id));
}

void MainWindow::insertCategoryOnMat(CategoryOnMat* cat)
{
    QListWidgetItem* item  = new QListWidgetItem();
    item->setSizeHint(cat->sizeHint());
    item->setData(Qt::UserRole, cat->getId());
    if(ui->tabMats->currentWidget()->objectName() == "tabMat1"){
        listWidgetMat1->addItem(item);
        listWidgetMat1->setItemWidget(item, cat);
    }
    else if(ui->tabMats->currentWidget()->objectName() == "tabMat2"){
        listWidgetMat2->addItem(item);
        listWidgetMat2->setItemWidget(item, cat);
    }
    else{
        listWidgetMat3->addItem(item);
        listWidgetMat3->setItemWidget(item, cat);
    }
}

//////////////////////////////////////////////
/// Заполнение меню последних соревнований ///
//////////////////////////////////////////////
void MainWindow::fillMenuLastCompetitions(){
    QDir dir = QDir::current();
    QFileInfoList lFiles = dir.entryInfoList({"*.db"}, QDir::Files, QDir::Time);
    if(lFiles.count() > 0){
        QActionGroup* gr = new QActionGroup(this);
        foreach(QFileInfo inf, lFiles){
            QAction* act = gr->addAction(inf.completeBaseName());
            act->setCheckable(true);
            connect(act, &QAction::triggered, [act, this](){
                controller->openCompetition(act->text());
            });
        }
        ui->mOpen->addActions(gr->actions());
    }
}


