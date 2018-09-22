#-------------------------------------------------
#
# Project created by QtCreator 2018-09-04T16:09:59
#
#-------------------------------------------------

QT       += core gui widgets
QT       += widgets printsupport

TARGET = Epoxy_Temp_Project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcustomplot.cpp \
    file_worker.cpp \
    dialog.cpp

HEADERS += \
        mainwindow.h \
    qcustomplot.h \
    file_worker.h \
    dialog.h \
    cbw.h

FORMS += \
        mainwindow.ui \
    dialog.ui
#Redefine to installation directory. Debug Only at static location
LIBS += "C:\Users\LEssary\Documents\Epoxy_Temp_Project\cbw32.dll"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
