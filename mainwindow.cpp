#include "mainwindow.h"
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
    //scene = new QGraphicsScene;
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
        // cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", i, 2);
        // a.append(cell->property("Value").toString());
        // delete cell;

        // cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", i, 3);
        // a.append(cell->property("Value").toString());
        // delete cell;

        // cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", i, 4);
        // a.append(cell->property("Value").toString());
        // delete cell;

        // cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", i, 5);
        // a.append(cell->property("Value").toString());
        // delete cell;

        // cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", i, 6);
        // a.append(cell->property("Value").toString());
        // delete cell;

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

    panel = new CategoryControlPanel(lAt);
    connect(panel, &CategoryControlPanel::sigChoosingCategory,
            [=](QString a ,QString b, QString c) { qDebug()<<a<<b<<c; });
    ui->verticalLayout->insertWidget(0, panel);


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
    // lr.append(rates("150.0", "5(10)"));
    // lr.append(rates("150.0", "6(10)"));
    // lr.append(rates("150.0", "7(10)"));
    // lr.append(rates("150.0", "8(10)"));

    // QList<athlete1round> lfr;

    // lfr.append(athlete1round("Иванов Иван", "Брянская область", "КМС", "150.0", "1(10)", "", 0));
    // lfr.append(athlete1round("Кузнецов Глеб", "Брянская область", "МС", "140.0", "1(10)", "", 1));
    // lfr.append(athlete1round("Сафронов Иван", "Брянская область", "1", "140.0", "1(10)", "", 2));
    // lfr.append(athlete1round("Перепелка Семен", "Брянская область", "1", "150.5", "1(10)", "", 3));
    // lfr.append(athlete1round("Круглов Дмитрий", "Брянская область", "КМС", "140.0", "1(10)", "", 4));

    //qDebug()<<"1";
    //FirstRound* fRound = new FirstRound(lfr);
    //qDebug()<<"2";

    //ItemHalfAndFinalOne3* item = new ItemHalfAndFinalOne3(la, lr, QList({1, 2, 0, 1}), QList({true, false}));
    //scene->addItem(fRound);
    //scene->addItem(item);
    //item->moveBy(0, fRound->getHeight() + 80);
    //scene->setSceneRect(0,0,300,300);
    qDebug()<<la.count();
    final_0 fData = final_0();
    QVariant data = QVariant::fromValue(fData);
    System_0* scene = new System_0(1, 0, la, data, "", "", "");
    scene->setRates(1, 0, lr);
    scene->setRates(1, 1, lr);
    scene->setRates(1, 2, lr);
    ui->gViewMain->setScene(scene);
    //ui->gViewMain->scene()->setSceneRect(QRectF(QPointF(),ui->gViewMain->size()));
    //ui->gViewMain->centerOn(-100, -100);
    //qDebug()<<scene->sceneRect();
}

MainWindow::~MainWindow()
{
    delete ui;
}
