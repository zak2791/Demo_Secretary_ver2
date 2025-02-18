#include "addingathletes.h"
#include <QTreeWidgetItem>
#include <QAxObject>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFileDialog>

AddingAthletes::AddingAthletes() : QTreeWidget()  {
    QStringList lst;
    lst<<tr("Категория")<<tr("Возраст")<<tr("Вес")<<tr("Спортсмен")
        <<tr("Общиий круг, финалы, 2 третьих места")
        <<tr("Общиий круг, финалы, 1 третье место");
    setHeaderLabels(lst);

    setSortingEnabled(true);

    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QDir::currentPath(), tr("Excel Files (*.xlsx)"));
    QAxObject* excel = new QAxObject("Excel.Application", 0);
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", filename);
    QAxObject* sheets = workbook->querySubObject("Sheets");
    QAxObject *StatSheet = sheets->querySubObject( "Item(const QVariant&)", QVariant(1) );

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

    QList<QString> sl;
    QList<QTreeWidgetItem*> lCategory;
    for(int i = 0; i < lAt.count(); i++){
        if(!sl.contains(lAt.at(i).at(3)) && lAt.at(i).at(3) != ""){
            sl.append(lAt.at(i).at(3));
            lCategory.append(new QTreeWidgetItem(this));
            lCategory.last()->setText(0, lAt.at(i).at(3));
        }
    }

    QList<QTreeWidgetItem*> lAge;
    for(int i = 0; i < lCategory.count(); i++){
        QList<QString> sAge;
        for(int j = 0; j < lAt.count(); j++){
            if(lAt.at(j).at(3) == sl.at(i)){
                if(!sAge.contains(lAt.at(j).at(4))){
                    sAge.append(lAt.at(j).at(4));
                    lAge.append(new QTreeWidgetItem(lCategory[i]));
                    lAge.last()->setText(1, lAt.at(j).at(4));
                    lAge.last()->setData(1, Qt::UserRole, lCategory.at(i)->text(0));
                }
            }
        }
    }

    QList<QRadioButton*> gRB;
    QList<QButtonGroup*> lGroup;
    //QList<QTreeWidgetItem*> lWeight;
    for(int i = 0; i < lCategory.count(); i++){
        QString cat = lCategory.at(i)->text(0);
        foreach(auto each, lAge){
            QString age = each->text(1);
            if(cat == each->data(1, Qt::UserRole).toString()){
                QList<QString> sWeight;
                if(each->data(1, Qt::UserRole).toString() == cat){
                    for(int j = 0; j < lAt.count(); j++){
                        QString weight = lAt.at(j).at(5);
                        if(cat == lAt.at(j).at(3) && age == lAt.at(j).at(4)){
                            if(!sWeight.contains(weight)){
                                sWeight.append(weight);
                                lWeight.append(new QTreeWidgetItem(each));
                                lWeight.last()->setText(2, weight);
                                lWeight.last()->setData(0, Qt::UserRole, cat);
                                lWeight.last()->setData(1, Qt::UserRole, age);
                                lWeight.last()->setData(2, Qt::UserRole, "-1");
                                int index = lWeight.count() - 1;
                                lGroup.append(new QButtonGroup);

                                ////////////////////////////////////////////
                                /// кнопка выбора системы проведения "0" ///
                                ////////////////////////////////////////////
                                gRB.append(new QRadioButton);
                                connect(gRB.last(), &QRadioButton::toggled, this, [this, index](bool b){if(b)lWeight.at(index)->setData(2, Qt::UserRole, "0");});
                                gRB.last()->setObjectName(cat + ":" + age + ":" + weight + ":" + "0");
                                lGroup.last()->addButton(gRB.last());
                                setItemWidget(lWeight.last(), 4, gRB.last());

                                ////////////////////////////////////////////
                                /// кнопка выбора системы проведения "1" ///
                                ////////////////////////////////////////////
                                gRB.append(new QRadioButton);
                                connect(gRB.last(), &QRadioButton::toggled, this, [this, index](bool b){if(b)lWeight.at(index)->setData(2, Qt::UserRole, "1");});
                                gRB.last()->setObjectName(cat + ":" + age + ":" + weight + ":" + "1");
                                lGroup.last()->addButton(gRB.last());
                                setItemWidget(lWeight.last(), 5, gRB.last());
                            }
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < lAt.count(); i++){
        foreach(auto each, lWeight){
            QString c = each->data(0, Qt::UserRole).toString();
            QString a = each->data(1, Qt::UserRole).toString();
            if(c == lAt.at(i).at(3) && a == lAt.at(i).at(4) && each->text(2) == lAt.at(i).at(5)){
                QTreeWidgetItem* item = new QTreeWidgetItem(each);
                item->setText(3, lAt.at(i).at(0));
            }
        }
    }
}

void AddingAthletes::closeEvent(QCloseEvent*)
{
    QList<QStringList> lSList;
    foreach(auto each, lWeight){
        QString cat = each->data(0, Qt::UserRole).toString();
        QString age = each->data(1, Qt::UserRole).toString();
        QString weight = each->text(2);
        QString system = each->data(2, Qt::UserRole).toString();
        QString header = cat + ":" + age + ":" + weight + ":" + system;
        QStringList sL;
        sL.append(header);
        foreach(auto each2, lAt){
            if(cat == each2.at(3) && age == each2.at(4) && weight == each2.at(5)){
                sL.append(each2.at(0) + ":" + each2.at(1) + ":" + each2.at(2));
            }
        }
        lSList.append(sL);
    }
    emit sigAddAthletes(lSList);
}
