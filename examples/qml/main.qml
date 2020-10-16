import QtQuick 2.0
import updatehub.Agent 2.0

Item {
    StateChange {
        Component.onCompleted: listen()

        onState: {
            if (State->id == AgentState.Download) {
               console.log("enter downloading state");
            }

            handler.cancel();
        }
    }
}
