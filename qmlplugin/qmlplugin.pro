TEMPLATE = lib

CONFIG += qt

QT = qml

TARGET = updatehubsdk-plugin

SOURCES += \
    agentplugin.cpp

HEADERS += \
    agentplugin.hpp

isEmpty(PREFIX):PREFIX = $$[QT_INSTALL_QML]/updatehub/Agent

LIBS += -L$$PREFIX/../src -lupdatehub-agent
INCLUDEPATH += $$PWD/../src

target.path = $$PREFIX

pluginfiles.files += $$PWD/qmldir
pluginfiles.path = $$PREFIX/qmlplugin

INSTALLS += target pluginfiles
