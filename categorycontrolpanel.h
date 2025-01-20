#ifndef CATEGORYCONTROLPANEL_H
#define CATEGORYCONTROLPANEL_H

#include <QWidget>
#include <QRadioButton>

struct age{
    QString name;
    QString current_weight;
    QList<QString> weights;
};

struct category{
    QString name;
    QString current_age;
    QList<age> ages;
};

struct category_age{
    QString _age;
    QString _category;
    QString weight;
};

namespace Ui {
class CategoryControlPanel;
}

class CategoryControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryControlPanel(QList<QStringList>, QWidget *parent = nullptr);
    ~CategoryControlPanel();

private:
    Ui::CategoryControlPanel *ui;
    QList<QRadioButton*> rbCat;
    QList<QRadioButton*> rbAge;
    QList<QRadioButton*> rbWeight;
    QString currentCategory;
    QString currentAge;
    QString currentWeight;
    QList<QStringList> sCA;
    QMap<QString, int> currAge;
    QMap<QString, int> currWeight;

private slots:
    void slotRbCategory(bool);
    void slotRbAge(bool);
    void slotRbWeight(bool);

signals:
    void sigChoosingCategory(QString, QString, QString);
};

#endif // CATEGORYCONTROLPANEL_H
