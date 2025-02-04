#ifndef ADDINGATHLETES_H
#define ADDINGATHLETES_H

#include <QTreeWidget>

class AddingAthletes : public QTreeWidget
{
    Q_OBJECT
public:
    AddingAthletes();

private:
    virtual void closeEvent(QCloseEvent*);
    QList<QTreeWidgetItem*> lWeight;
    QList<QStringList> lAt;

signals:
    void sigAddAthletes(QList<QStringList>);

};

#endif // ADDINGATHLETES_H
