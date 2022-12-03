QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
RC_FILE = passer.rc
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addentry.cpp \
    datawindow.cpp \
    main.cpp \
    initdialog.cpp \
    sqlitedbmanager.cpp \
    windowcreate.cpp \
    windowopen.cpp

HEADERS += \
    addentry.h \
    datawindow.h \
    initdialog.h \
    sqlitedbmanager.h \
    windowcreate.h \
    windowopen.h

FORMS += \
    addentry.ui \
    datawindow.ui \
    initdialog.ui \
    windowcreate.ui \
    windowopen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
