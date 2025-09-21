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

    portIn = settings->value("portIn", 5000).toInt();
    portOut = settings->value("portOut", 5001).toInt();
    portConn = settings->value("portConn", 5002).toInt();


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


    ui->sbIn->setValue(portIn);
    ui->sbOut->setValue(portOut);

    // connect(ui->leMat1, &QLineEdit::editingFinished, this, [this](){ip1 = ui->leMat1->text();});
    // connect(ui->leMat2, &QLineEdit::editingFinished, this, [this](){ip2 = ui->leMat2->text();});
    // connect(ui->leMat3, &QLineEdit::editingFinished, this, [this](){ip3 = ui->leMat3->text();});

    connect(ui->sbIn, &QSpinBox::valueChanged, this, [this](int value){portIn = value;});
    connect(ui->sbOut, &QSpinBox::valueChanged, this, [this](int value){portOut = value;});
    connect(ui->sbConn, &QSpinBox::valueChanged, this, [this](int value){portConn = value;});

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

    settings->setValue("portIn", portIn);
    settings->setValue("portOut", portOut);
    settings->setValue("portConn", portConn);

    settings->endGroup();
    accept();
}


