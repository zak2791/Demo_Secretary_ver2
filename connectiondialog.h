#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include "qsettings.h"
#include <QDialog>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();

private:
    Ui::ConnectionDialog *ui;

    QSettings* settings;
    QString ipLocal;

    int udpPort;

    int tcpPort;

private slots:
    void slotAccept(void);

};

#endif // CONNECTIONDIALOG_H
