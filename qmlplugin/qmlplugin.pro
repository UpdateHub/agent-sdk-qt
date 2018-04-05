TEMPLATE = lib

CONFIG += qt

QT = qml

TARGET = agentplugin

SOURCES += \
    agentplugin.cpp

HEADERS += \
    agentplugin.hpp

LIBS += -L../src -lupdatehubagent
INCLUDEPATH += $$PWD/../src

target.path = $$[QT_INSTALL_QML]/updatehub/Agent

pluginfiles.files += $$PWD/qmldir
pluginfiles.path = $$[QT_INSTALL_QML]/updatehub/Agent

INSTALLS += target pluginfiles
