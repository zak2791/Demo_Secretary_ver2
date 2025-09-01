#include "datatransfercontroller.h"
#include "qsettings.h"
#include "qtimer.h"

#include <QNetworkDatagram>


DataTransferController::DataTransferController(QObject* parent):QObject(parent){



    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    ipLocal = settings.value("ipLocal", "").toString();

    // ip1 = settings.value("ip1", "127.0.0.1").toString();
    // ip2 = settings.value("ip2", "127.0.0.1").toString();
    // ip3 = settings.value("ip3", "127.0.0.1").toString();

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



    QTimer* timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, [this](){
        if(ipLocal == "") return;
        int index = ipLocal.lastIndexOf(".");
        QString ipAddress = ipLocal.first(index) + ".255";
        qDebug()<<ipAddress;
        QNetworkDatagram datagram("hello", QHostAddress(ipAddress), udpPort1);
        qDebug()<<udpSocket->writeDatagram(datagram)<<ip1<<udpPort1;
    });
    timer1->start(5000);
    qDebug()<<"start timer";
    QByteArray data("Hello world!");
    qint16 checksum = qChecksum(data);

    char a = (checksum & 0xf000)>>12;
    char b = (checksum & 0x0f00)>>8;
    char c = (checksum & 0x00f0)>>4;
    char d = checksum & 0x000f;
    data.append(a).append(b).append(c).append(d);
    qDebug()<<data<<checksum;
    char _a = data.at(data.length() - 4);
    char _b = data.at(data.length() - 3);
    char _c = data.at(data.length() - 2);
    char _d = data.at(data.length() - 1);
    qint16 check = ((qint16)_a)<<12 | ((qint16)_b)<<8 | ((qint16)_c)<<4 | (qint16)_d;
    qDebug()<<check;
}

void DataTransferController::cangeConnection()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    ipLocal = settings.value("ipLocal", "").toString();

    // ip1 = settings.value("ip1", "127.0.0.1").toString();
    // ip2 = settings.value("ip2", "127.0.0.1").toString();
    // ip3 = settings.value("ip3", "127.0.0.1").toString();

    port1 = settings.value("port1", 5001).toInt();
    port2 = settings.value("port2", 5002).toInt();
    port3 = settings.value("port3", 5003).toInt();

    settings.endGroup();
}


