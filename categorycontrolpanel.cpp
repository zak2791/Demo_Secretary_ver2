#include "categorycontrolpanel.h"
#include "qforeach.h"
#include "ui_categorycontrolpanel.h"

CategoryControlPanel::CategoryControlPanel(QList<std::tuple<int, QString, QString, QString> > list, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CategoryControlPanel)
{
    ui->setupUi(this);

    tWeights = list;

    QRadioButton* btn;

    QStringList lCategory;



    foreach(auto each, tWeights){
        QString sCategory = std::get<1>(each);

        /////////////////////////////////////////////////
        /// заполнение списка кнопок выбора категорий ///
        /////////////////////////////////////////////////
        if(lCategory.count() == 0 || !lCategory.contains(sCategory))
            lCategory.append(sCategory);

        std::sort(lCategory.begin(), lCategory.end(), [](QString a, QString b){
            if(a.toLower() == "мужчины")
                return true;
            else
                return a < b;
        });
    }

    foreach(auto each, lCategory){
        btn = new QRadioButton(each);
        btn->setObjectName(each);
        ui->gbCategory->layout()->addWidget(btn);
        connect(btn, SIGNAL(toggled(bool)), this, SLOT(slotRbCategory(bool)));
        if(each == lCategory.first())
            btn->toggle();
    }
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->gbCategory->layout()->addItem(spacer); // Добавление шпателя в компоновщик


}

CategoryControlPanel::~CategoryControlPanel()
{
    delete ui;
}

int CategoryControlPanel::getId()
{
    QString category;
    foreach(auto each, ui->gbCategory->findChildren<QRadioButton*>()){
        if(each->isChecked()){
            category = each->text();
            break;
        }
    }
    QString age;
    foreach(auto each, ui->gbAge->findChildren<QRadioButton*>()){
        if(each->isChecked()){
            age = each->text();
            break;
        }
    }
    QString weight;
    foreach(auto each, ui->gbWeight->findChildren<QRadioButton*>()){
        if(each->isChecked()){
            weight = each->text();
            break;
        }
    }
    return getId(category, age, weight);
}

int CategoryControlPanel::getId(QString category, QString age, QString weight)
{
    int id = -1;
    foreach(auto each, tWeights){
        id = std::get<0>(each);
        QString sCategory = std::get<1>(each);
        QString sAge      = std::get<2>(each);
        QString sWeight   = std::get<3>(each);
        if(sCategory == category && sAge == age && sWeight == weight)
            break;
    }
    return id;
}

void CategoryControlPanel::slotRbCategory(bool b)
{
    if(b){
        QStringList lAge;
        currentCategory = static_cast<QRadioButton*>(sender())->text();

        qDeleteAll( ui->gbAge->findChildren<QWidget*>() );
        if(spacerItemAge != nullptr){
            ui->gbAge->layout()->removeItem(spacerItemAge);
            delete spacerItemAge;
        }

        foreach(auto each, tWeights){
            QString sCat = std::get<1>(each);
            QString sAge = std::get<2>(each);
            if(sCat == currentCategory && !lAge.contains(sAge))
                lAge.append(sAge);
        }
        std::sort(lAge.begin(), lAge.end());

        foreach(auto each, lAge){
            QRadioButton* btn = new QRadioButton(each);
            btn->setObjectName(each);
            ui->gbAge->layout()->addWidget(btn);
            connect(btn, SIGNAL(toggled(bool)), this, SLOT(slotRbAge(bool)));
            if(currAge.value(currentCategory).isEmpty()){
                if(each == lAge.first()){
                    btn->toggle();
                    currAge.insert(currentCategory, each);
                }
            }
            else{
                if(currAge.value(currentCategory) == each)
                    btn->toggle();
            }
        }
        spacerItemAge = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        ui->gbAge->layout()->addItem(spacerItemAge); // Добавление шпателя в компоновщик
    }
}

void CategoryControlPanel::slotRbAge(bool b)
{
    if(b){

        currentAge = static_cast<QRadioButton*>(sender())->text();
        currAge[currentCategory] = currentAge;
        QStringList lWeight;

        qDeleteAll( ui->gbWeight->findChildren<QWidget*>() );
        if(spacerItemWeight != nullptr){
            ui->gbWeight->layout()->removeItem(spacerItemWeight);
            delete spacerItemWeight;
        }

        foreach(auto each, tWeights){
            QString sCat = std::get<1>(each);
            QString sAge = std::get<2>(each);
            QString sWeight = std::get<3>(each);
            if(sCat == currentCategory && sAge == currentAge && !lWeight.contains(sWeight))
                lWeight.append(sWeight);
        }
        std::sort(lWeight.begin(), lWeight.end());

        foreach(auto each, lWeight){
            QRadioButton* btn = new QRadioButton(each);
            btn->setObjectName(each);
            ui->gbWeight->layout()->addWidget(btn);
            connect(btn, SIGNAL(toggled(bool)), this, SLOT(slotRbWeight(bool)));
            if(currWeight.value(currentCategory + ":" + currentAge).isEmpty()){
                if(each == lWeight.first()){
                    btn->toggle();
                    currWeight.insert(currentCategory + ":" + currentAge, each);
                }
            }
            else{
                if(currWeight.value(currentCategory + ":" + currentAge) == each)
                    btn->toggle();
            }
        }
        spacerItemWeight = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        ui->gbWeight->layout()->addItem(spacerItemWeight); // Добавление шпателя в компоновщик
    }

}

void CategoryControlPanel::slotRbWeight(bool b)
{
    if(b){
        QString currentWeight = static_cast<QRadioButton*>(sender())->text();
        currWeight[currentCategory + ":" + currentAge] = currentWeight;
        int id = getId(currentCategory, currentAge, currentWeight);
        emit sigChoosingCategory(id);
    }
}

void CategoryControlPanel::clickCategoryOnMat(QString c, QString a, QString w)
{
    qDebug()<<"click";
    QRadioButton* btn = ui->gbCategory->findChild<QRadioButton*>(c);
    btn->setChecked(true);
    //QThread::msleep(100);
    btn = ui->gbAge->findChild<QRadioButton*>(a);
    qDebug()<<btn<<a;

    btn->setChecked(true);
    btn = ui->gbWeight->findChild<QRadioButton*>(w);
    qDebug()<<btn;
    btn->setChecked(true);
}
