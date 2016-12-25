HEADERS += \
    HCServer.h \
    def.h \
    json.h \
    util.h \
    sqlconn.h \
    hcdef.h

SOURCES += \
    main.cpp \
    json.cpp \
    handlerequest.cpp \
    HCServer.cpp \
    main1.cpp \
    redis.cpp \
    util.cpp \
    sqlconn.cpp

CONFIG += TUFAO1 C++11
LIBS += -lhiredis
LIBS += -lcurl
QT +=network sql
LIBS +=-L/usr/local/lib -ltufao1 -lmysqlclient -lhiredis
INCLUDEPATH +=-I/usr/local/include -I/usr/include
