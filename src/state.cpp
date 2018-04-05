/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "state.hpp"

#include <QLocalSocket>

State::State(): QObject()
{
}

State::State(State::ID id, QLocalSocket *socket, QObject *parent):
    QObject(parent),
    m_id(id),
    m_socket(socket)
{
}

void State::cancel()
{
    m_socket->write("cancel");
    m_socket->close();
}

void State::tryAgain(int n)
{
    m_socket->write(QString("try_again %1").arg(n).toLocal8Bit());
    m_socket->close();
}
