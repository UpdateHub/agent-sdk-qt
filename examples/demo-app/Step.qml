import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11

Item {
    height: 40
    Layout.fillWidth: true

    property string title: ""
    property int status: Step.Pending
    property variant indicator: null

    enum Status {
        Pending,
        Completed,
        Failed
    }

    function statusColor() {
        switch (status) {
        case Step.Pending:
            return "#E0E0E0";
        case Step.Completed:
            return "#50E37D";
        case Step.Failed:
            return "#F8533D";
        }
    }

    function isAfterCurrentStep() {
        return indicator.steps.indexOf(indicator.step) > indicator.steps.indexOf(title);
    }

    function stepColor() {
        if (isAfterCurrentStep()) {
            status = Step.Completed;
        } else {
            status = Step.Pending;
        }

        return statusColor();
    }

    Column {
        spacing: 15
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            color: stepColor()
            height: 8

            Rectangle {
                color: parent.color
                height: parent.height
                width: radius * 4
                radius: 4
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: -4
                visible: indicator.steps.indexOf(title) === 0
            }

            Rectangle {
                color: parent.color
                height: parent.height
                width: radius * 4
                radius: 4
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.rightMargin: -4
                visible: indicator.steps.indexOf(title) === indicator.steps.length - 1
            }

            Rectangle {
                width: 30
                height: 30
                radius: width / 2
                border.color: stepColor()
                border.width: 8
                anchors.centerIn: parent

                BusyIndicator {
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    visible: indicator.step === title
                }
            }
        }

        Text {
            text: title
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
