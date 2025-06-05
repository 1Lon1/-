QT += netword
QT += sql
QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mytcpserver.cpp \
    database.cpp \
    functionsforserver.cpp
    
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mytcpserver.h \
    database.h \
    functionsforserver.h
    
    
    
    
    
    
    

