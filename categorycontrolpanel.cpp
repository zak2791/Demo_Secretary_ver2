#include "categorycontrolpanel.h"
#include "ui_categorycontrolpanel.h"

CategoryControlPanel::CategoryControlPanel(QList<std::tuple<int, QString, QString, QString> > list, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CategoryControlPanel)
{
    ui->setupUi(this);

    sCA = list;
    QList<QString> lCat;

    foreach(auto each, sCA){
        if(each.at(3) == "")
            break;
        if(!lCat.contains(each.at(3)))
            lCat.append(each.at(3));
        currWeight.insert(each.at(3) + ":" + each.at(4), 0);
    }

    foreach(auto each, lCat){
        currAge.insert(each, 0);
        rbCat.append(new QRadioButton(each));
    }

    foreach(auto each, rbCat){
        connect(each, SIGNAL(toggled(bool)), this, SLOT(slotRbCategory(bool)));
        ui->hbCategory->addWidget(each);
    }
    rbCat.at(0)->setChecked(true);

}

CategoryControlPanel::~CategoryControlPanel()
{
    delete ui;
}

void CategoryControlPanel::slotRbCategory(bool b)
{
    if(b){
        currentCategory = static_cast<QRadioButton*>(sender())->text();
        currentAge = "";
        foreach(auto each, rbAge)
            delete each;
        rbAge.clear();
        QList<QString> lAges;
        foreach(auto each, sCA){
            if(each.at(3) == currentCategory)
                if(!lAges.contains(each.at(4))){
                    rbAge.append(new QRadioButton(each.at(4)));
                    lAges.append(each.at(4));
                }
        }
        foreach(auto each, rbAge){
            connect(each, SIGNAL(toggled(bool)), this, SLOT(slotRbAge(bool)));
            ui->hbAge->addWidget(each);
        }
        int curAge = currAge[currentCategory];
        currentAge = rbAge[curAge]->text();
        rbAge[curAge]->toggle();
    }
}

void CategoryControlPanel::slotRbAge(bool b)
{
    if(b){
        foreach(auto each, rbWeight)
            delete each;
        rbWeight.clear();
        QList<QString> lWeights;

        currentAge = static_cast<QRadioButton*>(sender())->text();
        for(int i = 0; i < rbAge.count(); i++){
            if(rbAge.at(i)->text() == currentAge)
                currAge[currentCategory] = i;
        }

        foreach(auto each, sCA){
            if(each.at(3) == currentCategory && each.at(4) == currentAge){
                if(!lWeights.contains(each.at(5)))
                    lWeights.append(each.at(5));
            }
        }

        lWeights.sort();
        for(int i = 0; i <  lWeights.count(); i++){
            rbWeight.append(new QRadioButton(lWeights.at(i)));
            connect(rbWeight.at(i), SIGNAL(toggled(bool)), this, SLOT(slotRbWeight(bool)));
            ui->hbWeight->addWidget(rbWeight.at(i));
        }

        int curWei = currWeight[currentCategory + ":" + currentAge];
        rbWeight[curWei]->toggle();
    }
}

void CategoryControlPanel::slotRbWeight(bool b)
{
    if(b){
        currentWeight = static_cast<QRadioButton*>(sender())->text();
        for(int i = 0; i < rbWeight.count(); i++){
            if(rbWeight.at(i)->text() == currentWeight)
                currWeight[currentCategory + ":" + currentAge] = i;
        }
    }
    emit sigChoosingCategory(currentCategory, currentAge, currentWeight);
}
