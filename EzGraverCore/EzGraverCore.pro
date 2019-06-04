include(../common.pri)

QT += core
QT += serialport

TARGET = EzGraverCore
TEMPLATE = lib

DEFINES += EZGRAVERCORE_LIBRARY

SOURCES += ezgraver.cpp \
    ezgraver_decaker.cpp \
    ezgraver_nejev1.cpp \
    ezgraver_nejev2.cpp \
    ezgraver_nejev3.cpp \
    factory.cpp

HEADERS += ezgraver.h\
    ezgravercore_global.h \
    ezgraver_decaker.h \
    ezgraver_nejev1.h \
    ezgraver_nejev2.h \
    ezgraver_nejev3.h \
    factory.h \
    specifications.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
