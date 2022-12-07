# If release-buid -> run windeploy applications, that will collect all the dlls
CONFIG(release, debug|release) {
    QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/release
}

# Ця конфігурація розносить вихідні файли проекту при компіляції у різні підкаталоги: moc, rcc, ui, win32.
# Share all project output files by directories
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui
unix:OBJECTS_DIR = unix
win32:OBJECTS_DIR = win32
macx:OBJECTS_DIR = mac (edited)


QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
RC_FILE = passer.rc


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addentry.cpp \
    datainfo.cpp \
    datawindow.cpp \
    dbmanager.cpp \
    editentry.cpp \
    hash.cpp \
    main.cpp \
    initdialog.cpp \
    sqlitedbmanager.cpp \
    userinfo.cpp \
    windowcreate.cpp \
    windowopen.cpp

HEADERS += \
    addentry.h \
    datainfo.h \
    datawindow.h \
    dbmanager.h \
    editentry.h \
    hash.h \
    initdialog.h \
    sqlitedbmanager.h \
    userinfo.h \
    windowcreate.h \
    windowopen.h

FORMS += \
    addentry.ui \
    datawindow.ui \
    editentry.ui \
    initdialog.ui \
    windowcreate.ui \
    windowopen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
