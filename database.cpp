#include "database.h"
#include "qmessagebox.h"

DataBase::DataBase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    query = new QSqlQuery;
    query->exec(" PRAGMA synchronous = OFF, journal_mode = MEMORY");
}

DataBase::~DataBase(){
    if(db.open())
        db.close();
    delete query;
}

bool DataBase::createBase(QString name){
    if(db.isOpen())
        db.close();
    db.setDatabaseName(name);
    if (!db.open())
        return false;
    QMessageBox msgBox;
    QString str = "CREATE TABLE sportsmen "
                  "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "name  TEXT, team TEXT, range TEXT,  "
                  "id_category INTEGER, "
                  "place TEXT DEFAULT '', "
                  "rate TEXT DEFAULT '', "
                  "UNIQUE (name, team, id_category))";
    if(!query->exec(str)){
        msgBox.setText("Ошибка создания таблицы sportsmen " + db.lastError().text());
        msgBox.exec();
        db.close();
        return false;
    }

    str = "CREATE TABLE categories "
          "(id INTEGER PRIMARY KEY AUTOINCREMENT, id_system INTEGER, status INTEGER DEFAULT 0, "
          "category TEXT, age TEXT, weight TEXT, data TEXT DEFAULT '') ";

    if(!query->exec(str)){
        msgBox.setText("Ошибка создания таблицы system_0 " + db.lastError().text());
        msgBox.exec();
        db.close();
        return false;
    }

    return true;
}

bool DataBase::createBaseOnMat(QString base){

}

QList<std::tuple<int, int, int, QList<athlete>, QString, QString, QString, QString> > DataBase::openBase(QString base){
    if(!db.isOpen())
        db.close();
    db.setDatabaseName(base);
    QList<std::tuple<int, int, int, QList<athlete>, QString, QString, QString, QString>> lTuple;
    if (!db.open())
        return QList<std::tuple<int, int, int, QList<athlete>, QString, QString, QString, QString>>();
    QMessageBox msgBox;
    QString sqlCategories("SELECT * FROM categories;");
    QString sqlSportsmen("SELECT * FROM sportsmen WHERE id_category = ?; ") ;
    QSqlQuery q;
    //q.exec(" PRAGMA synchronous = OFF, journal_mode = MEMORY");
    if(!query->exec(sqlCategories)){
        msgBox.setText("Ошибка чтения таблицы категорий " + db.lastError().text());
        msgBox.exec();
        db.close();
        return QList<std::tuple<int, int, int, QList<athlete>, QString, QString, QString, QString>>();
    }
    while(query->next()){
        int id = query->value("id").toInt();
        int id_system = query->value("id_system").toInt();
        int status = query->value("status").toInt();
        QList<athlete> lA;
        QString data = query->value("data").toString();
        QString category = query->value("category").toString();
        QString age = query->value("age").toString();
        QString weight = query->value("weight").toString();
        q.prepare(sqlSportsmen);
        q.bindValue(0, id);
        if(!q.exec()){
            msgBox.setText("Ошибка чтения спортсмена " + db.lastError().text());
            msgBox.exec();
            db.close();
            return QList<std::tuple<int, int, int, QList<athlete>, QString, QString, QString, QString>>();
        }
        while(q.next()){
            athlete ath;
            ath.id = q.value("id").toInt();
            ath.name = q.value("name").toString();
            ath.team = q.value("team").toString();
            ath.range = q.value("range").toString();
            ath.rate = q.value("rate").toString();
            ath.place = q.value("place").toString();
            lA.append(ath);
        }
        lTuple.append(std::tuple(id, id_system, status, lA, data, category, age, weight));
    }
    return lTuple;
}

bool DataBase::addCategories(QList<QStringList> list)
{
    QMessageBox msgBox;
    QString sqlCategories("INSERT INTO categories (id_system, category, age, weight) VALUES (?, ?, ?, ?);") ;
    QString sqlSportsmen("INSERT INTO sportsmen (id_category, name, team, range) VALUES (?, ?, ?, ?);") ;
    QSqlQuery q;
    q.exec(" PRAGMA synchronous = OFF, journal_mode = MEMORY");
    foreach(auto each, list){
        QStringList listCategory = each.at(0).split(":");
        QString category = listCategory.at(0);
        QString age      = listCategory.at(1);
        QString weight   = listCategory.at(2);
        int id_system    = listCategory.at(0).toInt();
        if(id_system == -1)
            continue;
        query->prepare(sqlCategories);
        query->bindValue(0, id_system);
        query->bindValue(1, category);
        query->bindValue(2, age);
        query->bindValue(3, weight);
        if(!query->exec()){
            msgBox.setText("Ошибка добавления категории " + db.lastError().text());
            msgBox.exec();
            db.close();
            return false;
        }
        int id = query->lastInsertId().toInt();
        for(int i = 1; i < each.count(); i++){
            QStringList listSportsmen = each.at(i).split(":");
            QString name  = listSportsmen.at(0);
            QString team  = listSportsmen.at(1);
            QString range = listSportsmen.at(2);
            q.prepare(sqlSportsmen);
            q.bindValue(0, id);
            q.bindValue(1, name);
            q.bindValue(2, team);
            q.bindValue(3, range);
            if(!q.exec()){
                msgBox.setText("Ошибка добавления спортсмена " + db.lastError().text());
                msgBox.exec();
                db.close();
                return false;
            }
        }
    }
    return true;
}
