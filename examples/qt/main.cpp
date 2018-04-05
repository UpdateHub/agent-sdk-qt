#include <QCoreApplication>
#include <QDebug>

#include <updatehubagent/statechangelistener.hpp>
#include <updatehubagent/state.hpp>
#include <updatehubagent/agent.hpp>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    StateChangeListener l;
    l.listen();

    QObject::connect(&l, &StateChangeListener::stateChanged, [=](StateChangeListener::Action action, State *state) {
        if (action == StateChangeListener::ActionEnter && state->id() == State::Downloading) {
            qDebug("enter downloading state");
        }

        state->cancel();
    });

    return app.exec();
}
