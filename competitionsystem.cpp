#include "competitionsystem.h"

CompetitionSystem::CompetitionSystem(int _id, int _id_system, QList<athlete> list, QVariant _data, QString _category, QString _age, QString _weight) {
    id = _id;
    id_system = _id_system;
    lAthlete = list;
    data = _data;
    category = _category;
    age = _age;
    weight = _weight;
}
