#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "categorycontrolpanel.h"
#include "qlabel.h"

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
    void setControlPanel(QList<std::tuple<int, QString, QString, QString>>);

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene;

    CategoryControlPanel* panel;

    QStatusBar* statusBar;
    QLabel lblStatus;



};
#endif // MAINWINDOW_H
