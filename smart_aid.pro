QT+= core gui sql charts
QT+= sql
QT+= printsupport
QT+= charts serialport
QT+= location qml quickwidgets
QT+= core network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


INCLUDEPATH +="$$PWD\cpp"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    categories.cpp \
    connection.cpp \
    crises.cpp \
    dons.cpp \
    employes.cpp \
    evenements.cpp \
    main.cpp \
    maincrises.cpp \
    maindon.cpp \
    mainevenement.cpp \
    mainwindow.cpp \
    necessiteux.cpp \
    $$PWD/cpp/qrcodegen.cpp \
    piechart.cpp \
    qcustomplot.cpp \
    rendezvous.cpp \
    smtp.cpp \
    users.cpp

HEADERS += \
    arduino.h \
    categories.h \
    connection.h \
    crises.h \
    dons.h \
    employes.h \
    evenements.h \
    mainwindow.h \
    necessiteux.h \
    $$PWD/cpp/qrcodegen.hpp \
    piechart.h \
    qcustomplot.h \
    rendezvous.h \
    smtp.h \
    users.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    ressources.qrc

RC_ICONS = employe128.ico

DISTFILES +=
