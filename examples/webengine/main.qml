import QtQuick 2.0
import updatehub.Agent 1.0
import QtWebEngine 1.1
import QtWebChannel 1.0

WebEngineView {
    url: "index.html"

    Agent {
        id: agent
    }

    StateChangeListener {
        id: listener

        Component.onCompleted: listen()
    }

    Component.onCompleted: {
        webChannel.registerObject("Agent", agent);
        webChannel.registerObject("StateChangeListener", listener);
    }
}
