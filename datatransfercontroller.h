#ifndef DATATRANSFERCONTROLLER_H
#define DATATRANSFERCONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
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

    int portConn;       //порт контроля подключения к коврам
    int portIn;
    int portOut;

    QTcpSocket* tcpSocket;
    QTcpServer* tcpServer;
    QMap<int, QTcpSocket*> listClientSockets;

    QUdpSocket* udpSocket;

    QByteArray addCheckSum(QString);
    QString controlCheckSum(QByteArray);

private slots:
    void slotNewConnection(void);
    void slotReadyRead(void);
    void slotDisconnect(void);

signals:
    void sigConnectToMat(int);

};

#endif // DATATRANSFERCONTROLLER_H
