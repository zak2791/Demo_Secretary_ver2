#ifndef DATATRANSFERCONTROLLER_H
#define DATATRANSFERCONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>

class DataTransferController : public QObject
{
    Q_OBJECT
public:
    DataTransferController(QObject* parent = nullptr);
    void cangeConnection(void);

private:

    QString ipLocal;

    QString ip1;
    QString ip2;
    QString ip3;

    int udpPort1;
    int udpPort2;
    int udpPort3;

    int port1;
    int port2;
    int port3;

    QTcpSocket* socketMat1;
    QTcpSocket* socketMat2;
    QTcpSocket* socketMat3;

    QUdpSocket* udpSocket;

};

#endif // DATATRANSFERCONTROLLER_H
