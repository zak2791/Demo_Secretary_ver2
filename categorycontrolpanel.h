#ifndef CATEGORYCONTROLPANEL_H
#define CATEGORYCONTROLPANEL_H

#include <QWidget>
#include <QRadioButton>

namespace Ui {
class CategoryControlPanel;
}

class CategoryControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryControlPanel(QList<std::tuple<int, QString, QString, QString>>,
                                  QWidget *parent = nullptr);
    ~CategoryControlPanel();
    int getId(void);

private:
    Ui::CategoryControlPanel *ui;

    QString currentCategory;
    QString currentAge;

    QList<std::tuple<int, QString, QString, QString>> tWeights;
    QMap<QString, QString> currAge;                                 //key -> "category"
    QMap<QString, QString> currWeight;                              //key -> "category:age"
    int getId(QString, QString, QString);


private slots:
    void slotRbCategory(bool);
    void slotRbAge(bool);
    void slotRbWeight(bool);

signals:
    void sigChoosingCategory(int);
};

#endif // CATEGORYCONTROLPANEL_H
