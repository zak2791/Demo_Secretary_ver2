/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *aCreate;
    QAction *aOpen;
    QAction *aExit;
    QAction *aAdd;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *gViewMain;
    QGraphicsView *gViewOnMat;
    QMenuBar *menubar;
    QMenu *mCompetition;
    QMenu *mAthletes;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 600);
        aCreate = new QAction(MainWindow);
        aCreate->setObjectName("aCreate");
        aOpen = new QAction(MainWindow);
        aOpen->setObjectName("aOpen");
        aExit = new QAction(MainWindow);
        aExit->setObjectName("aExit");
        aAdd = new QAction(MainWindow);
        aAdd->setObjectName("aAdd");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        centralwidget->setMouseTracking(false);
        centralwidget->setTabletTracking(false);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gViewMain = new QGraphicsView(centralwidget);
        gViewMain->setObjectName("gViewMain");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gViewMain->sizePolicy().hasHeightForWidth());
        gViewMain->setSizePolicy(sizePolicy);
        gViewMain->setMouseTracking(false);
        gViewMain->setTabletTracking(false);

        horizontalLayout->addWidget(gViewMain);

        gViewOnMat = new QGraphicsView(centralwidget);
        gViewOnMat->setObjectName("gViewOnMat");
        sizePolicy.setHeightForWidth(gViewOnMat->sizePolicy().hasHeightForWidth());
        gViewOnMat->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(gViewOnMat);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        mCompetition = new QMenu(menubar);
        mCompetition->setObjectName("mCompetition");
        mAthletes = new QMenu(menubar);
        mAthletes->setObjectName("mAthletes");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(mCompetition->menuAction());
        menubar->addAction(mAthletes->menuAction());
        mCompetition->addAction(aCreate);
        mCompetition->addAction(aOpen);
        mCompetition->addAction(aExit);
        mAthletes->addAction(aAdd);

        retranslateUi(MainWindow);
        QObject::connect(aExit, &QAction::triggered, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        aCreate->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        aOpen->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        aExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        aAdd->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\267 \320\261\321\203\321\204\320\265\321\200\320\260 \320\276\320\261\320\274\320\265\320\275\320\260", nullptr));
        mCompetition->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\320\265\320\262\320\275\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        mAthletes->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
