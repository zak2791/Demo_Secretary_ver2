QT       += core gui widgets axcontainer sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcompetition.cpp \
    addingathletes.cpp \
    categorycontrolpanel.cpp \
    categorycreator.cpp \
    categoryonmat.cpp \
    competitionsystem.cpp \
    controller.cpp \
    database.cpp \
    jsonconverter.cpp \
    ledwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    system_0.cpp \
    system_0_common.cpp \
    system_0_final.cpp

HEADERS += \
    addcompetition.h \
    addingathletes.h \
    categorycontrolpanel.h \
    categorycreator.h \
    categoryonmat.h \
    competitionsystem.h \
    controller.h \
    database.h \
    jsonconverter.h \
    ledwidget.h \
    main.h \
    mainwindow.h \
    system_0.h \
    system_0_common.h \
    system_0_final.h

FORMS += \
    addcompetition.ui \
    categorycontrolpanel.ui \
    mainwindow.ui

TRANSLATIONS += \
    DemoSecretaryVer2_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/from mat.svg \
    images/on mat.svg

RESOURCES += \
    resources.qrc
