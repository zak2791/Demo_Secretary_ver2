#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "HalfAndFinalOne3.h"
#include "firstround.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    QList<athlete> la;
    la.append(athlete("Иванов Иван", "Брянская область", "КМС"));
    la.append(athlete("Петров Петр", "Брянская область", "КМС"));
    la.append(athlete("Сидоров Сидор", "Брянская область", "КМС"));
    la.append(athlete("Кузнецов Кузнец", "Брянская область", "КМС"));
    QList<rates> lr;
    lr.append(rates("150.0", "1(10)"));
    lr.append(rates("150.0", "2(10)"));
    lr.append(rates("150.0", "3(10)"));
    lr.append(rates("150.0", "4(10)"));
    lr.append(rates("150.0", "5(10)"));
    lr.append(rates("150.0", "6(10)"));
    lr.append(rates("150.0", "7(10)"));
    lr.append(rates("150.0", "8(10)"));

    QList<athlete1round> lfr;

    lfr.append(athlete1round("Иванов Иван", "Брянская область", "КМС", "150.0", "1(10)", ""));
    lfr.append(athlete1round("Кузнецов Глеб", "Брянская область", "МС", "140.0", "1(10)", ""));
    lfr.append(athlete1round("Сафронов Иван", "Брянская область", "1", "140.0", "1(10)", ""));
    lfr.append(athlete1round("Перепелка Семен", "Брянская область", "1", "150.5", "1(10)", ""));
    lfr.append(athlete1round("Круглов Дмитрий", "Брянская область", "КМС", "140.0", "1(10)", ""));

    //qDebug()<<"1";
    FirstRound* fRound = new FirstRound(lfr);
    //qDebug()<<"2";

    ItemHalfAndFinalOne3* item = new ItemHalfAndFinalOne3(la, lr, QList({1, 2, 0, 1}), QList({true, false}));
    scene->addItem(fRound);
    scene->addItem(item);
    item->moveBy(0, fRound->getHeight() + 80);
    //scene->setSceneRect(0,0,300,300);
    ui->gViewMain->setScene(scene);
    //ui->gViewMain->scene()->setSceneRect(QRectF(QPointF(),ui->gViewMain->size()));
    //ui->gViewMain->centerOn(-100, -100);
    //qDebug()<<scene->sceneRect();
}

MainWindow::~MainWindow()
{
    delete ui;
}
