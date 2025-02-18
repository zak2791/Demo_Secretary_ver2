#include "matsstatus.h"
#include "qboxlayout.h"

MatsStatus::MatsStatus(QWidget* parent) : QWidget(parent) {

    pixClose.load(":/images/close_envelope.png");
    pixClose = pixClose.scaledToHeight(15, Qt::SmoothTransformation);

    pixOpen.load(":/images/envelope_gray.png");
    pixOpen = pixOpen.scaledToHeight(15, Qt::SmoothTransformation);

    pixCloseRed.load(":/images/close_envelope_red.png");
    pixCloseRed = pixCloseRed.scaledToHeight(15, Qt::SmoothTransformation);

    pixOpenRed.load(":/images/envelope_red.png");
    pixOpenRed = pixOpenRed.scaledToHeight(15, Qt::SmoothTransformation);

    led1 = new LEDWidget(2);
    led2 = new LEDWidget(2);
    led3 = new LEDWidget(2);

    QFrame* line1 = new QFrame;
    line1->setFrameShape(QFrame::VLine);
    line1->setFrameShadow(QFrame::Sunken);
    QFrame* line2 = new QFrame;
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);

    QHBoxLayout* hBox = new QHBoxLayout;

    lblMat1 = new QLabel("Ковёр 1");
    lblMat2 = new QLabel("Ковёр 2");
    lblMat3 = new QLabel("Ковёр 3");

    lblMat1Sending = new QLabel;
    lblMat1Sending->setPixmap(pixCloseRed);
    lblMat1Recieving = new QLabel;
    lblMat1Recieving->setPixmap(pixOpen);

    lblMat2Sending = new QLabel;
    lblMat2Sending->setPixmap(pixClose);
    lblMat2Recieving = new QLabel;
    lblMat2Recieving->setPixmap(pixOpenRed);

    lblMat3Sending = new QLabel;
    lblMat3Sending->setPixmap(pixClose);
    lblMat3Recieving = new QLabel;
    lblMat3Recieving->setPixmap(pixOpen);

    hBox->addWidget(lblMat1);
    hBox->addWidget(led1);
    hBox->addWidget(lblMat1Sending);
    hBox->addWidget(lblMat1Recieving);
    hBox->addWidget(line1);
    hBox->addWidget(lblMat2);
    hBox->addWidget(led2);
    hBox->addWidget(lblMat2Sending);
    hBox->addWidget(lblMat2Recieving);
    hBox->addWidget(line2);
    hBox->addWidget(lblMat3);
    hBox->addWidget(led3);
    hBox->addWidget(lblMat3Sending);
    hBox->addWidget(lblMat3Recieving);

    hBox->setAlignment(led1, Qt::AlignVCenter);
    hBox->setAlignment(led2, Qt::AlignVCenter);
    hBox->setAlignment(led3, Qt::AlignVCenter);

    setLayout(hBox);

}
