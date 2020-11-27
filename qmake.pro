TEMPLATE = subdirs

CONFIG += ordered

isEmpty(PLUGIN):PLUGIN

contains(PLUGIN, QML) {
    SUBDIRS = src qmlplugin
} else {
    SUBDIRS = src
}
