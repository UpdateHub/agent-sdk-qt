/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "statechangelistener.hpp"

#include <QLocalServer>
#include <QLocalSocket>
#include <QFile>

#include "state.hpp"

static State::ID stateFromString(const QString &str) {
    if (str == "idle")
        return State::Idle;
    if (str == "poll")
        return State::Poll;
    if (str == "probe")
        return State::Probe;
    if (str == "downloading")
        return State::Downloading;
    if (str == "downloaded")
        return State::Downloaded;
    if (str == "installing")
        return State::Installing;
    if (str == "installed")
        return State::Installed;
    if (str == "exit")
        return State::Exit;
    if (str == "rebooting")
        return State::Rebooting;

    return State::Invalid;
}

StateChangeListener::StateChangeListener(QObject *parent) : QObject(parent)
{
    m_server = new QLocalServer;

    if (!QFile::exists("/usr/share/updatehub/state-change-callbacks.d/10-updatehub-sdk-integration")) {
        qFatal("updatehub-sdk-statechange-trigger not found!");
    }
}

void StateChangeListener::listen()
{
    QLocalServer::removeServer("/run/updatehub-statechange.sock");

    m_server->close();
    m_server->listen("/run/updatehub-statechange.sock");

    connect(m_server, &QLocalServer::newConnection, [=]() {
        QLocalSocket *socket = m_server->nextPendingConnection();

        connect(socket, &QLocalSocket::disconnected, [=]() {
            socket->deleteLater();
        });

        connect(socket, &QLocalSocket::readyRead, [=]() {
            parseData(socket, socket->readAll());
        });
    });
}

void StateChangeListener::parseData(QLocalSocket *socket, const QByteArray &data)
{
    QStringList lines = QString::fromLocal8Bit(data).split('\n');

    foreach (const QString &line, lines) {
        if (line.isEmpty())
            continue;

        QStringList args = line.split(' ');

        if (args.first() == "error" && args.size() > 1) {
            emit errorOccurred(args.mid(1, -1).join(" "));
            socket->close();
            return;
        }

        // invalid arguments
        if (args.size() < 2) {
            socket->close();
            return;
        }

        Action action = ActionInvalid;
        if (args.first() == "enter")
            action = ActionEnter;
        if (args.first() == "leave")
            action = ActionLeave;

        State::ID id = stateFromString(args.last());
        if (id == State::Invalid)
            return;
        if (action == ActionInvalid)
            return;

        State *state = new State(id, socket, this);

        emit stateChanged(action, state);

        if (QObject::receivers(SIGNAL(stateChanged(Action, State*))) == 0)
            state->done();
    }
}
