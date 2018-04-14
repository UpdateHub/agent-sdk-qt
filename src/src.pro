TEMPLATE = lib

CONFIG += qt create_pc create_prl no_install_prl

QT = qml

TARGET = updatehubagent

SOURCES += \
    statechangelistener.cpp \
    state.cpp \
    agent.cpp

HEADERS += \
    statechangelistener.hpp \
    state.hpp \
    agent.hpp

target.path = $$PREFIX/usr/lib

headers.path = $$PREFIX/usr/include/updatehubagent
headers.files = statechangelistener.hpp state.hpp agent.hpp

QMAKE_PKGCONFIG_NAME = updatehubagent
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$headers.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig

INSTALLS += target headers
