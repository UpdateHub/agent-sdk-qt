import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.11
import updatehub.Agent 1.0 as UpdateHub

Image {
    source: "bg.jpg"

    property string version: ""
    property string currentState: ""

    UpdateHub.Agent {
        id: updatehub
    }

    UpdateHub.StateChangeListener {
        Component.onCompleted: listen()

        onStateChanged: {
            switch (state.id()) {
            case UpdateHub.AgentState.Downloading:
                currentState = "Downloading";
                break;
            case UpdateHub.AgentState.Installing:
                currentState = "Installing";
                break;
            case UpdateHub.AgentState.Rebooting:
                currentState = "Rebooting";
            }

            state.done();
        }
    }

    Timer {
        interval: 0
        running: true
        repeat: false

        onTriggered: {
            var info = updatehub.info();
            if (typeof info != "undefined") {
               version = info.firmware.version;
            }
        }
    }

    Image {
        source: "updatehub.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: frame.top
        anchors.bottomMargin: 20
    }

    Rectangle {
        id: frame
        color: "#fff"
        radius: 10
        width: 640
        height: 480
        anchors.centerIn: parent

        Item {
            anchors.fill: parent

            Image {
                id: padlock

                source: "locked.png"
                width: 180
                smooth: true
                mipmap: true
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -40

                ColorOverlay {
                    anchors.fill: parent
                    source: parent
                    color: "#5CA7DF"
                }
            }

            Column {
                spacing: 10

                anchors.top: padlock.bottom
                anchors.topMargin: 40
                anchors.horizontalCenter: parent.horizontalCenter

                Item {
                    width: 600
                    anchors.horizontalCenter: parent.horizontalCenter

                    StepIndicator {
                        anchors.fill: parent

                        steps: ["Checking", "Downloading", "Installing", "Rebooting"]
                        step: currentState
                    }
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20

                Text {
                    font.pixelSize: 12
                    text: {
                        return "<i>Version: " + version + "</i>";
                    }
                }
            }
        }
    }

    Rectangle {
        width: label.width + 40
        height: 40
        color: "#5CA7DF"
        radius: 8
        anchors.top: frame.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: currentState === "" ? 1 : 0.2
        enabled: currentState === ""


        Text {
            id: label
            text: "CHECK FOR UPDATES"
            color: "#ffffff"
            font.bold: true
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                currentState = "Checking";

                var probe = updatehub.probe("");

                if (typeof probe != "undefined") {
                    if (!probe["update-available"]) {
                        currentState = "";
                    }
                }
            }
        }
    }

    Image {
        source: "ossystems.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
    }
}
