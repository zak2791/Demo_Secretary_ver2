QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    competitionsystem.cpp \
    main.cpp \
    mainwindow.cpp \
    system_0.cpp \
    system_0_common.cpp \
    system_0_final.cpp

HEADERS += \
    competitionsystem.h \
    main.h \
    mainwindow.h \
    system_0.h \
    system_0_common.h \
    system_0_final.h

FORMS += \
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
