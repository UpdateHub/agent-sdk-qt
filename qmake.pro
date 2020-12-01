TEMPLATE = subdirs

CONFIG += ordered

contains(PLUGIN, QML) {
    SUBDIRS = src qmlplugin
} else {
    SUBDIRS = src
}
