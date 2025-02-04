#include "categorycreator.h"
#include "system_0.h"

CategoryCreator::CategoryCreator() {}

CompetitionSystem *CategoryCreator::createCategory(//int,
                                                   //int,
                                                   //QString,
                                                   //QString,
                                                   //QString,
                                                   QStringList list)
{
    QString header = list.at(0);
    int system = header.split(":").at(3).toInt();
    switch (system) {
    case 0:
        //return new System_0();
        break;
    default:
        break;
    }
    return nullptr;
}
