import QtQuick 2.0
import updatehub.Agent 1.0

Item {
    StateChangeListener {
        Component.onCompleted: listen()

        onStateChanged: {
            if (action == StateChangeListener.ActionEnter && state.id() == AgentState.Downloading) {
               console.log("enter downloading state");
            }

            state.cancel();
        }
    }
}
