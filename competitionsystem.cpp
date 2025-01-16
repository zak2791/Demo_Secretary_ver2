#include "competitionsystem.h"

CompetitionSystem::CompetitionSystem(int _id, int _id_system, QList<athlete> list, QVariant _data) {
    id = _id;
    id_system = _id_system;
    lAthlete = list;
    data = _data;
    qDebug()<<lAthlete.count()<<"count";
}
