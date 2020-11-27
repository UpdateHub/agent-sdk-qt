# updatehub agent SDK for Qt/QML

The updatehub agent SDK for Qt/QML provides a set of classes to enable programs
written in both Qt and QML to interact with the updatehub agent.

### Documentation

See [docs/README.md](docs/README.md) for some basic documentation of provided classes.

### Examples

* [Qt](examples/qt)
* [QML](examples/qml)
* [WebEngine](examples/webengine)

### Building

```
qmake
make
make install
```

You can change install prefix by setting PREFIX variable:

```
qmake PREFIX=/usr
```

You can set to install the QML plugin by setting PLUGIN variable:

```
qmake PLUGIN=QML
```
