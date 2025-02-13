#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "categorycontrolpanel.h"
#include "controller.h"
#include "qlabel.h"
#include "qlistwidget.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int getMat(void);

private slots:
    void setControlPanel(QList<std::tuple<int, QString, QString, QString>>);
    void setCategory(int);
    void insertCategoryOnMat(CategoryOnMat*);

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene;
    Controller* controller;
    CategoryControlPanel* panel;

    QStatusBar* statusBar;
    QLabel lblStatus;
    QListWidget* listWidgetMat1;
    QListWidget* listWidgetMat2;
    QListWidget* listWidgetMat3;

    void fillMenuLastCompetitions(void);
    CategoryOnMat* cat;

};
#endif // MAINWINDOW_H
