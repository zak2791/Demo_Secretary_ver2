#ifndef CATEGORYCREATOR_H
#define CATEGORYCREATOR_H

#include "competitionsystem.h"

class CategoryCreator
{
public:
    CategoryCreator();
    CompetitionSystem* createCategory(//int,          //id в базе данных
                                      //int,          //id категории
                                      //QString,      //категория
                                      //QString,      //возраст
                                      //QString,      //вес
                                      QStringList   //
                                      );
};

#endif // CATEGORYCREATOR_H
