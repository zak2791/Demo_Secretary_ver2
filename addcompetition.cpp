#include "addcompetition.h"
#include "ui_addcompetition.h"

#include <QMessageBox>
#include <QFileInfo>



AddCompetition::AddCompetition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompetition)
{
    ui->setupUi(this);

    setWindowTitle("Новое соревнование");

    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->btnCreate, SIGNAL(clicked()), this, SLOT(createCompetitions()));

}

AddCompetition::~AddCompetition()
{
    delete ui;
}

void AddCompetition::createCompetitions(){
    QString name = ui->leName->text();
    QString city = ui->leCity->text();
    QString start = ui->deStart->text();
    QString finish = ui->deFinish->text();
    QMessageBox msgBox;
    if(name.trimmed() == "" || city.trimmed() == ""){
        msgBox.setText("Все поля должны быть заполнены!");
        msgBox.exec();
        return;
    }
    QString baza_name = name + "_" + city + "_" + start + "_" + finish + ".db";
    if(QFileInfo::exists(baza_name)){
        msgBox.setText("Соревнование уже существует!");
        msgBox.exec();
        return;
    }
    emit sigNewBase(baza_name);
    accept();
}
