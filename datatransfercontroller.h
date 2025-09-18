#ifndef DATATRANSFERCONTROLLER_H
#define DATATRANSFERCONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>

class DataTransferController : public QObject
{
    Q_OBJECT
public:
    DataTransferController(QString*, QObject* parent = nullptr);
    void changeConnection(void);
    QList<int> sendData(int, QList<std::tuple<int, QString>>);
    bool removeCategory(int, int);

private:

    QString* currentCompetitionTitle;
    QString ipLocal;

    QHostAddress ip1;
    QHostAddress ip2;
    QHostAddress ip3;

    int udpPort;

    int tcpPort;

    QTcpSocket* tcpSocket;

    QUdpSocket* udpSocket;

    QByteArray addCheckSum(QString);
    QString controlCheckSum(QByteArray);

signals:
    void sigConnectToMat(int);

};

#endif // DATATRANSFERCONTROLLER_H
