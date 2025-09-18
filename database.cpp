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
                  "UNIQUE (name, team, id_category))";
    if(!query->exec(str)){
        msgBox.setText("Ошибка создания таблицы sportsmen " + db.lastError().text());
        msgBox.exec();
        db.close();
        return false;
    }

    str = "CREATE TABLE categories "
          "(id INTEGER PRIMARY KEY AUTOINCREMENT, id_system INTEGER, "
          "category TEXT, age TEXT, weight TEXT, data TEXT DEFAULT '') ";

    if(!query->exec(str)){
        msgBox.setText("Ошибка создания таблицы system_0 " + db.lastError().text());
        msgBox.exec();
        db.close();
        return false;
    }

    str = "CREATE TABLE categories_on_mats "
          "(id INTEGER PRIMARY KEY AUTOINCREMENT, id_category INTEGER, id_system INTEGER, mode INTEGER, mat INTEGER, "
          "status INTEGER DEFAULT 0, "
          "data TEXT);";

    if(!query->exec(str)){
        msgBox.setText("Ошибка создания таблицы categories_on_mats " + db.lastError().text());
        msgBox.exec();
        db.close();
        return false;
    }

    db.close();

    if(!createBaseOnMat(name.first(name.length() - 3)  + "_Mat1.db"))
        qDebug()<<"Не удалось создать базу ковра 1";
    if(!createBaseOnMat(name.first(name.length() - 3)  + "_Mat2.db"))
        qDebug()<<"Не удалось создать базу ковра 2";
    if(!createBaseOnMat(name.first(name.length() - 3)  + "_Mat3.db"))
        qDebug()<<"Не удалось создать базу ковра 3";

    db.setDatabaseName(name);
    if (!db.open())
        return false;
    return true;
}

bool DataBase::createBaseOnMat(QString name){
    db.setDatabaseName(name);
    if (!db.open())
        return false;

    QSqlQuery query;

    QMessageBox msgBox;

    QString str = "CREATE TABLE categories "
          "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "id_category INTEGER, "
           "id_system INTEGER, "
           "mode INTEGER, "
           "status INTEGER DEFAULT 0, "
           "category TEXT, "
           "age TEXT, "
           "weight TEXT, "
           "data TEXT);";

    if(!query.exec(str)){
        msgBox.setText("Ошибка создания таблицы categories " + db.lastError().text());
        msgBox.exec();
        db.close();
        return false;
    }

    str = "CREATE TABLE referee "
          "(id INTEGER PRIMARY KEY AUTOINCREMENT, id_referee INTEGER, name TEXT, region TEXT, range TEXT,"
          "data TEXT);";

    if(!query.exec(str)){
        msgBox.setText("Ошибка создания таблицы referee " + db.lastError().text());
        msgBox.exec();
        db.close();
        return false;
    }

    db.close();

    return true;
}

QList<std::tuple<int, int, QList<athlete>, QString, QString, QString, QString> > DataBase::getCategories(QString base){
    if(db.isOpen())
        db.close();
    db.setDatabaseName(base);
    QList<std::tuple<int, int, QList<athlete>, QString, QString, QString, QString>> listData;
    if (!db.open())
        return listData;
    QMessageBox msgBox;
    QString sqlCategories("SELECT * FROM categories;");
    QString sqlSportsmen("SELECT * FROM sportsmen WHERE id_category = ?; ") ;
    QSqlQuery q;
    if(!query->exec(sqlCategories)){
        msgBox.setText("Ошибка чтения таблицы категорий " + db.lastError().text());
        msgBox.exec();
        return listData;
    }
    while(query->next()){
        int id = query->value("id").toInt();
        int id_system = query->value("id_system").toInt();
        //int status = query->value("status").toInt();
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
            return listData;
        }
        while(q.next()){
            athlete ath;
            ath.id = q.value("id").toInt();
            ath.name = q.value("name").toString();
            ath.team = q.value("team").toString();
            ath.range = q.value("range").toString();
            lA.append(ath);
        }
        listData.append(std::tuple(id, id_system, lA, data, category, age, weight));
    }
    return listData;
}

/////////////////////////////////////////////////////////////////////////////
/// \brief DataBase::addCategories
/// Создание категорий при добавлении спортсменов
/// \param list
/// \return
//////////////////////////////////
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
        int id_system    = listCategory.at(3).toInt();
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
                return false;
            }
        }
    }
    return true;
}

void DataBase::writeData(int id, QString data)
{
    QMessageBox msgBox;
    QString sql("UPDATE categories SET data = ? WHERE id = ?");
    query->prepare(sql);
    query->bindValue(0, data);
    query->bindValue(1, id);
    if(!query->exec()){
        msgBox.setText("Ошибка обновления данных " + db.lastError().text());
        msgBox.exec();
    }
}

int DataBase::createCategoryOnMat(int id_cat, int id_sys, int mode, int mat, QString data)
{
    QMessageBox msgBox;

    QString sql = "INSERT INTO categories_on_mats (id_category, id_system, mode, mat, data) VALUES (?, ?, ?, ?, ?)";
    query->prepare(sql);
    query->bindValue(0, id_cat);
    query->bindValue(1, id_sys);
    query->bindValue(2, mode);
    query->bindValue(3, mat);
    query->bindValue(4, data);
    if(!query->exec()){
        msgBox.setText("Ошибка вставки категории на ковер " + db.lastError().text());
        msgBox.exec();
        return -1;
    }
    return query->lastInsertId().toInt();
}

QList<int> DataBase::deleteCategoryFromMat(int id_category_on_mat)
{
    QMessageBox msgBox;
    QString sql("SELECT id_category, mode FROM categories_on_mats WHERE id = %1 ;");
    sql = sql.arg(QString::number(id_category_on_mat));
    if(!query->exec(sql)){
        msgBox.setText("Ошибка чтения categories_on_mats " + db.lastError().text());
        msgBox.exec();
        return QList<int>();
    }
    if(!query->next()){
        msgBox.setText("Ошибка чтения id_category, mode FROM categories_on_mats " + db.lastError().text());
        msgBox.exec();
        return QList<int>();
    }
    int id_category = query->value(0).toInt();
    int mode = query->value(1).toInt();
    sql = "DELETE FROM categories_on_mats WHERE id = " + QString::number(id_category_on_mat) + ";";
    if(!query->exec(sql)){
        msgBox.setText("Ошибка удаления из categories_on_mats " + db.lastError().text());
        msgBox.exec();
        return QList<int>();
    }
    return {id_category, mode};
}

void DataBase::updateStatusCategoryOnMat(QList<int> listId, int status)
{
    qDebug()<<"updateStatusCategoryOnMat";
    QMessageBox msgBox;
    QString sql("UPDATE categories_on_mats SET status = ? WHERE id = ?");
    foreach(int id, listId){
        query->prepare(sql);
        query->bindValue(0, status);
        query->bindValue(1, id);
        if(!query->exec()){
            msgBox.setText("Ошибка обновления статуса " + db.lastError().text());
            msgBox.exec();
        }
    }
}

QList<std::tuple<int, int, int, int, int, int, QString, QString, QString, QString> > DataBase::getCategoriesOnMats()
{
    QMessageBox msgBox;
    QList<std::tuple<int, int, int, int, int, int, QString, QString, QString, QString>> lTpl;
    QString sql("SELECT A.id, A.id_category, A.id_system, A.mode, A.mat, A.status, A.data, B.id, B.category, B.age, B.weight FROM categories_on_mats A "
                "LEFT JOIN "
                "categories B "
                "ON B.id = A.id_category;");
    if(!query->exec(sql)){
        msgBox.setText("Ошибка чтения таблицы категорий на коврах " + query->lastError().text());
        qDebug()<<query->lastError().text();
        msgBox.exec();
        db.close();
        return QList<std::tuple<int, int, int, int, int, int, QString, QString, QString, QString>>();
    }
    while(query->next()){
        int id              = query->value(0).toInt();
        int id_category     = query->value(1).toInt();
        int id_system       = query->value(2).toInt();
        int mode            = query->value(3).toInt();
        int mat             = query->value(4).toInt();
        int status          = query->value(5).toInt();
        QString data        = query->value(6).toString();
        QString category    = query->value(8).toString();
        QString age         = query->value(9).toString();
        QString weight      = query->value(10).toString();
        lTpl.append(std::tuple<int, int, int, int, int, int, QString, QString, QString, QString>
                    (id, id_category, id_system, mode, mat, status, category, age, weight, data));
    }
    return lTpl;
}
