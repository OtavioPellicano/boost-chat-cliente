TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/include/boost -lboost_system -lboost_chrono -lboost_thread -lboost_timer


SOURCES += \
        main.cpp \
    clienteboost.cpp \
    mensagem.cpp \
    interface.cpp \
    opmm-StringCsv/StringCsv.cpp

HEADERS += \
    clienteboost.h \
    mensagem.h \
    interface.h \
    opmm-StringCsv/StringCsv.h
