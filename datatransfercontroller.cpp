#include "datatransfercontroller.h"
#include "qsettings.h"
#include "qtimer.h"

#include <QNetworkDatagram>


DataTransferController::DataTransferController(QString * title, QObject* parent):QObject(parent){

    currentCompetitionTitle = title;

    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    ipLocal = settings.value("ipLocal", "").toString();

    tcpPort = settings.value("tcpPort", 5001).toInt();
    udpPort = settings.value("udpPort", 5000).toInt();

    settings.endGroup();

    ip1 = QHostAddress();
    ip2 = QHostAddress();
    ip3 = QHostAddress();

    udpSocket = new QUdpSocket(this);

    connect(udpSocket, &QUdpSocket::readyRead, this, [this](){
        QNetworkDatagram datagram;
        while (udpSocket->hasPendingDatagrams()) {
            datagram = udpSocket->receiveDatagram();
        }
        QString data = datagram.data();
        //qDebug()<<data;
        if(data == "Mat1") ip1 = datagram.senderAddress();
        else if(data == "Mat2") ip2 = datagram.senderAddress();
        else if(data == "Mat3") ip3 = datagram.senderAddress();
    });

    tcpSocket = new QTcpSocket(this);
    // connect(socketMat1, &QAbstractSocket::readyRead, this, [](){
    //     socketMat1->read()
    // });
    // connect(tcpSocket, &QAbstractSocket::connected, this, [](){
    //     qDebug()<<"connected";
    // });
    // connect(tcpSocket, &QAbstractSocket::disconnected, this, [this](){
    //     //socketMat1->connectToHost(ip1, tcpPort);
    // });
    // connect(tcpSocket, &QAbstractSocket::errorOccurred, this, [](QAbstractSocket::SocketError error){
    //     qDebug()<<"error 1 = "<<error;
    // });



    QTimer* timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, [this](){
        if(ipLocal == "") return;
        int len = (*currentCompetitionTitle).length();
        if(len < 4) return;
        QString title = (*currentCompetitionTitle).first(len - 3);
        //qDebug()<<title;
        //if(title == "") return;
        int index = ipLocal.lastIndexOf(".");
        QString ipAddress = ipLocal.first(index) + ".255";
        QNetworkDatagram datagram(title.toUtf8(), QHostAddress(ipAddress), udpPort);
        udpSocket->writeDatagram(datagram);
    });
    timer1->start(5000);

}

void DataTransferController::changeConnection()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    ipLocal = settings.value("ipLocal", "").toString();

    tcpPort = settings.value("tcpPort", 5001).toInt();
    udpPort = settings.value("udpPort", 5002).toInt();

    settings.endGroup();
}




QList<int> DataTransferController::sendData(int mat, QList<std::tuple<int, QString>> listIdAndData)
{
    QHostAddress address;
    if(mat ==1) address = ip1;
    else if (mat == 2) address = ip2;
    else address = ip3;

    QList<int> listId;  //список id успешно отправленных категорий

    tcpSocket->connectToHost(address, tcpPort);
    if(!tcpSocket->waitForConnected(1000))
        return listId;
    qDebug()<<"connected";
    foreach(auto each, listIdAndData){
        int id = std::get<0>(each);
        QString data = std::get<1>(each);
        tcpSocket->write(addCheckSum(data));
        if(!tcpSocket->waitForReadyRead(5000)){
            tcpSocket->close();
            return listId;
        }
        QByteArray ba = tcpSocket->readAll();
        if(ba.contains("Ok"))
            listId.append(id);
    }
    tcpSocket->close();
    return listId;
}

QByteArray DataTransferController::addCheckSum(QString data)
{
    QByteArray ba = data.toUtf8();
    qint16 checksum = qChecksum(ba);
    qDebug()<<"c"<<checksum<<ba;
    char a = (checksum & 0xf000)>>12;
    char b = (checksum & 0x0f00)>>8;
    char c = (checksum & 0x00f0)>>4;
    char d = checksum & 0x000f;
    ba.append(a).append(b).append(c).append(d);
    return ba;
}

QString DataTransferController::controlCheckSum(QByteArray _ba)
{
    QByteArray ba = _ba;
    char a = ba.at(ba.length() - 4);
    char b = ba.at(ba.length() - 3);
    char c = ba.at(ba.length() - 2);
    char d = ba.at(ba.length() - 1);
    qint16 check = ((qint16)a)<<12 | ((qint16)b)<<8 | ((qint16)c)<<4 | (qint16)d;
    ba = ba.first(ba.length() - 4);
    if(qChecksum(ba) == check) return ba;
    else return "";
}

