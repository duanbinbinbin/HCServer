HEADERS += \
    HCServer.h \
    def.h \
    json.h

SOURCES += \
    main.cpp \
    json.cpp \
    handlerequest.cpp \
    HCServer.cpp \
    main1.cpp \
    redis.cpp

CONFIG += TUFAO1 C++11
LIBS += -lhiredis
