#include "datatransfercontroller.h"
#include "qsettings.h"
#include "qtimer.h"

#include <QNetworkDatagram>
#include <QNetworkInterface>

DataTransferController::DataTransferController(QObject* parent):QObject(parent){
    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    ip1 = settings.value("ip1", "127.0.0.1").toString();
    ip2 = settings.value("ip2", "127.0.0.1").toString();
    ip3 = settings.value("ip3", "127.0.0.1").toString();

    port1 = settings.value("port1", 5001).toInt();
    port2 = settings.value("port2", 5001).toInt();
    port3 = settings.value("port3", 5001).toInt();

    udpPort1 = settings.value("udpPort1", 5000).toInt();
    udpPort2 = settings.value("udpPort2", 5000).toInt();
    udpPort3 = settings.value("udpPort3", 5000).toInt();

    settings.endGroup();

    udpSocket = new QUdpSocket(this);

    connect(udpSocket, &QUdpSocket::readyRead, this, [this](){
        QNetworkDatagram datagram;
        while (udpSocket->hasPendingDatagrams()) {
            datagram = udpSocket->receiveDatagram();
        }
        qDebug()<<datagram.data();
    });

    socketMat1 = new QTcpSocket(this);
    connect(socketMat1, &QAbstractSocket::readyRead, this, [](){

    });
    connect(socketMat1, &QAbstractSocket::connected, this, [](){
        qDebug()<<"connected";
    });
    connect(socketMat1, &QAbstractSocket::disconnected, this, [](){
        qDebug()<<"disconnected";
    });
    connect(socketMat1, &QAbstractSocket::errorOccurred, this, [](QAbstractSocket::SocketError error){
        qDebug()<<"error 1 = "<<error;
    });

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            qDebug() << address.toString();
    }

    QTimer* timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, [this](){
        QNetworkDatagram datagram("hello", QHostAddress("192.168.3.255"), udpPort1);
        qDebug()<<udpSocket->writeDatagram(datagram)<<ip1<<udpPort1;
    });
    timer1->start(5000);
    qDebug()<<"start timer";

}

void DataTransferController::cangeConnection()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    ip1 = settings.value("ip1", "127.0.0.1").toString();
    ip2 = settings.value("ip2", "127.0.0.1").toString();
    ip3 = settings.value("ip3", "127.0.0.1").toString();

    port1 = settings.value("port1", 5001).toInt();
    port2 = settings.value("port2", 5002).toInt();
    port3 = settings.value("port3", 5003).toInt();

    settings.endGroup();
}


