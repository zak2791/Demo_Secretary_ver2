#include "datatransfercontroller.h"
#include "qsettings.h"
#include "qtimer.h"

#include <QNetworkDatagram>
#include <QMessageBox>

DataTransferController::DataTransferController(QString * title, QObject* parent):QObject(parent){

    currentCompetitionTitle = title;

    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    ipLocal = settings.value("ipLocal", "").toString();

    portIn = settings.value("portIn", 5000).toInt();
    portOut = settings.value("portOut", 5000).toInt();
    portConn = settings.value("portConn", 5002).toInt();

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
        if(data == "Mat1") {
            ip1 = datagram.senderAddress();
            emit sigConnectToMat(1);
        }
        else if(data == "Mat2") {
            ip2 = datagram.senderAddress();
            emit sigConnectToMat(2);
        }
        else if(data == "Mat3") {
            ip3 = datagram.senderAddress();
            emit sigConnectToMat(3);
        }
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
        int index = ipLocal.lastIndexOf(".");
        QString ipAddress = ipLocal.first(index) + ".255";
        QNetworkDatagram datagram(title.toUtf8(), QHostAddress(ipAddress), portConn);
        udpSocket->writeDatagram(datagram);
    });
    timer1->start(5000);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &DataTransferController::slotNewConnection);
    qDebug()<<portIn;
    if (!tcpServer->listen(QHostAddress::Any, portIn)) {
        QMessageBox::critical(nullptr, tr("Tcp server"),
                              tr("Unable to start the server: %1.")
                                  .arg(tcpServer->errorString()));
    }

}

void DataTransferController::changeConnection()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Connections");

    ipLocal = settings.value("ipLocal", "").toString();

    portIn = settings.value("portIn", 5000).toInt();
    portOut = settings.value("portOut", 5001).toInt();
    portConn = settings.value("portConn", 5002).toInt();

    settings.endGroup();

    if(tcpServer->isListening()) tcpServer->close();
    if (!tcpServer->listen(QHostAddress::Any, portIn)) {
        QMessageBox::critical(nullptr, tr("Tcp server"),
                              tr("Unable to start the server: %1.")
                                  .arg(tcpServer->errorString()));
    }
}




QList<int> DataTransferController::sendData(int mat, QList<std::tuple<int, QString>> listIdAndData)
{
    QHostAddress address;
    if(mat ==1) address = ip1;
    else if (mat == 2) address = ip2;
    else address = ip3;

    QList<int> listId;  //список id успешно отправленных категорий
    tcpSocket->connectToHost(address, portOut);
    if(!tcpSocket->waitForConnected(1000))
        return listId;
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

bool DataTransferController::removeCategory(int mat, int id)
{
    QHostAddress address;
    if(mat == 0) address = ip1;
    else if (mat == 1) address = ip2;
    else address = ip3;

    qDebug()<<address<<ip1;

    QTcpSocket sock;
    sock.connectToHost(address, portOut);
    if(!sock.waitForConnected(1000))
        return false;
    QString data = "Remove" + QString::number(id);
    qDebug()<<data;
    sock.write(addCheckSum(data));
    if(!sock.waitForReadyRead(1000)){
        sock.close();
        return false;
    }

    QByteArray ba = sock.readAll();
    qDebug()<<"ba = "<<ba;
    sock.close();
    if(!ba.contains("Ok"))
        return false;
    return true;
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

void DataTransferController::slotNewConnection()
{
    //tcpServer->pauseAccepting();
    QTcpSocket* socket = tcpServer->nextPendingConnection();

    //listClientSockets.insert(socket->socketDescriptor(), socket);
    qDebug()<<socket;
    connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);
    //connect(clientConnection, &QAbstractSocket::disconnected, tcpServer, &QTcpServer::resumeAccepting);
    connect(socket, &QAbstractSocket::readyRead, this, &DataTransferController::slotReadyRead);

}

void DataTransferController::slotReadyRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray ba = socket->readAll();
    qDebug()<<"slotReadyRead"<<ba;//<<listClintSockets;


}

void DataTransferController::slotDisconnect()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    int desc = socket->socketDescriptor();
    qDebug()<<desc;
    socket->deleteLater();
    listClientSockets.remove(desc);
    qDebug()<<listClientSockets;
}

