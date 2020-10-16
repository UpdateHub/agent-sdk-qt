TEMPLATE = lib

CONFIG += qt create_pc create_prl no_install_prl

QT = qml

TARGET = updatehub-agent

SOURCES += \
    listener.cpp \
    agent.cpp \
    handler.cpp

HEADERS += \
    listener.hpp \
    state.hpp \
    agent.hpp \
    handler.hpp \

INTERFACE += \
    UpdateHubAgent \
    UpdateHubListener

isEmpty(PREFIX):PREFIX = /usr/local

target.path = $$PREFIX/lib

interface.path = $$PREFIX/include
interface.files = UpdateHubAgent UpdateHubListener

headers.path = $$PREFIX/include/updatehub-agent
headers.files = listener.hpp state.hpp agent.hpp handler.hpp

QMAKE_PKGCONFIG_NAME = updatehub-agent
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$PREFIX/include
QMAKE_PKGCONFIG_DESTDIR = pkgconfig

INSTALLS += target headers interface
