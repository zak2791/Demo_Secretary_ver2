#include "mainwindow.h"
#include "controller.h"
#include "system_0.h"
#include "ui_mainwindow.h"

#include <QAxObject>
//#include "HalfAndFinalOne3.h"
//#include "firstround.h"
#include "main.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar = new QStatusBar(this);
    statusBar->addWidget(&lblStatus);
    setStatusBar(statusBar);

    QAction* actAdd = ui->aAdd;
    Controller* controller = new Controller(this);
    connect(ui->aCreate,    &QAction::triggered,         controller, &::Controller::createCompetition);
    connect(ui->aOpen,      &QAction::triggered,         controller, &::Controller::openCompetition);
    connect(ui->aAdd,       &QAction::triggered,         controller, &::Controller::addAthletes);
    connect(controller,     &Controller:: sigCompetition, [actAdd, this](QString s) {
        if(s == "")
            actAdd->setEnabled(false);
        else{
            actAdd->setEnabled(true);
            lblStatus.setText(s.left(s.lastIndexOf(".")).replace("_", " "));
        }
    });

    QAxObject* excel = new QAxObject("Excel.Application", 0);
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", "C:/Users/Colorfull/Desktop/test.xlsx");
    QAxObject* sheets = workbook->querySubObject("Sheets");
    QAxObject *StatSheet = sheets->querySubObject( "Item(const QVariant&)", QVariant(1) );

    QList<QStringList> lAt;
    for(int i = 1; i < 1000; i++){
        QStringList a;
        QVariant result;
        for(int j = 1; j < 7; j++){
            QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", i, j);
            if(j == 1)
                result = cell->property("Value");
            a.append(cell->property("Value").toString());
            delete cell;
        }

        lAt.append(a);

        if(result.toString() == "")
            break;
    }

    workbook->dynamicCall( "Close()" );
    excel->dynamicCall( "Quit()" );
    delete StatSheet;
    delete sheets;
    delete workbook;
    delete workbooks;
    delete excel;

    // panel = new CategoryControlPanel(lAt);
    // connect(panel, &CategoryControlPanel::sigChoosingCategory,
    //         [=](QString a ,QString b, QString c) { qDebug()<<a<<b<<c; });
    // ui->verticalLayout->insertWidget(0, panel);


    QList<athlete> la;
    la.append(athlete(0, "Иванов Иван", "Брянская область", "КМС", "", "", "1"));
    la.append(athlete(1, "Петров Петр", "Брянская область", "КМС", "", "", "3"));
    la.append(athlete(2, "Сидоров Сидор", "Брянская область", "КМС", "", "", "4"));
    la.append(athlete(3, "Кузнецов Кузнец", "Брянская область", "КМС", "", "", "2"));
    QList<rates> lr;
    lr.append(rates(0, "150.0", "1(10)"));
    lr.append(rates(1, "150.0", "2(10)"));
    lr.append(rates(2, "150.0", "3(10)"));
    lr.append(rates(3, "150.0", "4(10)"));

    //QVariant::fromValue(lr);

    qDebug()<<la.count();
    final_0 fData = final_0();
    QVariant data = QVariant::fromValue(fData);
    //System_0* scene = new System_0(1, 0, la, data, "", "", "");
    //scene->setRates(1, 0, QVariant::fromValue(lr));
    //scene->setRates(1, 1, QVariant::fromValue(lr));
    //scene->setRates(1, 2, QVariant::fromValue(lr));
    //ui->gViewMain->setScene(scene);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setControlPanel(std::tuple<int, QString, QString, QString> list)
{
    panel = findChild<CategoryControlPanel*>();
    if(panel != nullptr){
        ui->verticalLayout->removeWidget(panel);
    }
    delete panel;

    qDebug()<<list;
    // panel = new CategoryControlPanel(list);
    // connect(panel, &CategoryControlPanel::sigChoosingCategory,
    //         [=](QString a ,QString b, QString c) { qDebug()<<a<<b<<c; });
    // ui->verticalLayout->insertWidget(0, panel);
}


