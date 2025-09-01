
 #include "categoryonmat.h"
#include "ledwidget.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qpushbutton.h"

CategoryOnMat::CategoryOnMat(int id_,
                             int id_category_,
                             int id_system_,
                             int mode_,
                             int _status,
                             QString category,
                             QString age,
                             QString weight,
                             QString _data,
                             QWidget *parent) : QFrame(parent) {

    id = id_;
    id_category = id_category_,
    id_system = id_system_;
    mode = mode_;
    status = _status;
    sCategory = category;
    sAge = age;
    sWeight = weight;
    data = _data;
    lblInfo = new QLabel(this);
    if(id_system == 0){
        if(mode == 0){
            lblInfo->setText("Общий круг");
        }
        else if(mode == 1){
            lblInfo->setText("Полуфинал");
        }
        else if(mode == 1){
            lblInfo->setText("Финал");
        }
    }

    QList<QFrame*> lFrame;
    for(int i = 0; i < 4; i++){
        QFrame* line = new QFrame(this);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        lFrame.append(line);
    }
    QVBoxLayout* layout = new QVBoxLayout(this);

    QHBoxLayout* hbFirstRow = new QHBoxLayout(this);

    setFrameStyle(QFrame::WinPanel);
    lblCategory = new QLabel(category, this);
    lblCategory->setFrameStyle(QFrame::NoFrame);
    lblAge = new QLabel(age, this);
    lblWeight = new QLabel(weight, this);

    hbFirstRow->addWidget(lblCategory);
    hbFirstRow->addWidget(lFrame.at(0));
    hbFirstRow->addWidget(lblAge);
    hbFirstRow->addWidget(lFrame.at(1));
    hbFirstRow->addWidget(lblWeight);
    hbFirstRow->addStretch();

    QHBoxLayout* hbThirdRow = new QHBoxLayout(this);
    LEDWidget* LedDeliveredOnmat = new LEDWidget(0, this);
    LEDWidget* LedInWork = new LEDWidget(1, this);
    LEDWidget* LedChangeRead= new LEDWidget(1, this);

    QPushButton* btnRemove = new QPushButton("Убрать с ковра", this);
    connect(btnRemove, &QPushButton::clicked, [this](){emit sigRemoveFromMat(id);});
    QPushButton* buttonRead = new QPushButton("Сбросить статус", this);

    hbThirdRow->addWidget(new QLabel("Доставлен на ковер", this));
    hbThirdRow->addWidget(LedDeliveredOnmat);
    QPushButton* btnSend = new QPushButton("Отослать на ковёр");
    hbThirdRow->addWidget(btnSend);
    hbThirdRow->addWidget(lFrame.at(2));

    hbThirdRow->addWidget(new QLabel("В работе/отработан", this));
    hbThirdRow->addWidget(LedInWork);
    hbThirdRow->addWidget(lFrame.at(3));
    hbThirdRow->addWidget(new QLabel("Оценки прочитаны", this));
    hbThirdRow->addWidget(LedChangeRead);
    hbThirdRow->addWidget(buttonRead);

    QLayout* lay = hbThirdRow->layout();
    lay->setAlignment(LedDeliveredOnmat, Qt::AlignVCenter);
    lay->setAlignment(LedInWork, Qt::AlignVCenter);
    lay->setAlignment(LedChangeRead, Qt::AlignVCenter);

    hbThirdRow->addStretch();
    hbThirdRow->addWidget(btnRemove);

    layout->addLayout(hbFirstRow);
    layout->addWidget(lblInfo);
    layout->addLayout(hbThirdRow);

    setLayout(layout);

    connect(btnSend, &QPushButton::clicked, this, &CategoryOnMat::sigSendData);
    connect(btnSend, &QPushButton::clicked, this, [this](){getDataToSend();});

}

QString CategoryOnMat::getDataToSend()
{
    qDebug()<<data;
    return data;
}

void CategoryOnMat::mousePressEvent(QMouseEvent *)
{
    qDebug()<<sCategory<<sAge<<sWeight;
    emit sigClick(sCategory, sAge, sWeight);
}
