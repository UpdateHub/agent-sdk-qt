import QtQuick 2.4
import QtQuick.Layouts 1.11

Item {
    id: indicator

    property variant steps: []
    property string step: ""

    Component.onCompleted: {
        for (var i in steps) {
            var component = Qt.createComponent("Step.qml");
            component.createObject(layout, { title: steps[i], indicator: indicator});
        }
    }

    function error(step) {
        for (var i in layout.children) {
            console.log(layout.children[i].title)
        }
    }

    RowLayout {
        id: layout

        spacing: 0
        anchors.fill: parent
    }
}
