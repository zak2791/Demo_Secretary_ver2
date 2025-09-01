#include "connectiondialog.h"
#include "qhostaddress.h"
#include "ui_connectiondialog.h"
#include <QNetworkInterface>

ConnectionDialog::ConnectionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    ui->cbIPLocalNet->addItem("");

    QStringList lAddr;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){
            lAddr.append(address.toString());
            ui->cbIPLocalNet->addItem(address.toString());
        }
    }


    settings = new QSettings("settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("Connections");

    ipLocal = settings->value("ipLocal", "").toString();

    port1 = settings->value("port1", 5001).toInt();
    port2 = settings->value("port2", 5001).toInt();
    port3 = settings->value("port3", 5001).toInt();

    udpPort1 = settings->value("udpPort1", 5000).toInt();
    udpPort2 = settings->value("udpPort2", 5000).toInt();
    udpPort3 = settings->value("udpPort3", 5000).toInt();

    settings->endGroup();

    int index = ui->cbIPLocalNet->findText(ipLocal);
    if(index != -1){
        ui->cbIPLocalNet->setCurrentIndex(index);
    }

    connect(ui->cbIPLocalNet, &QComboBox::currentTextChanged, this, [this](QString text){
        ipLocal = text;
    });

    // ui->leMat1->setText(ip1);
    // ui->leMat2->setText(ip2);
    // ui->leMat3->setText(ip3);


    ui->sbMat1->setValue(port1);
    ui->sbMat2->setValue(port2);
    ui->sbMat3->setValue(port3);

    // connect(ui->leMat1, &QLineEdit::editingFinished, this, [this](){ip1 = ui->leMat1->text();});
    // connect(ui->leMat2, &QLineEdit::editingFinished, this, [this](){ip2 = ui->leMat2->text();});
    // connect(ui->leMat3, &QLineEdit::editingFinished, this, [this](){ip3 = ui->leMat3->text();});

    connect(ui->sbMat1, &QSpinBox::valueChanged, this, [this](int value){port1 = value;});
    connect(ui->sbMat2, &QSpinBox::valueChanged, this, [this](int value){port2 = value;});
    connect(ui->sbMat3, &QSpinBox::valueChanged, this, [this](int value){port3 = value;});

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ConnectionDialog::slotAccept);

}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::slotAccept()
{
    settings = new QSettings("settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("Connections");

    settings->setValue("ipLocal", ipLocal);

    settings->setValue("port1", port1);
    settings->setValue("port2", port2);
    settings->setValue("port3", port3);

    settings->setValue("udpPort1", udpPort1);
    settings->setValue("udpPort2", udpPort2);
    settings->setValue("udpPort3", udpPort3);

    settings->endGroup();
    accept();
}


