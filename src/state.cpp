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
    m_socket(socket),
    m_done(false)
{
}

void State::done()
{
    m_socket->close();
    m_done = true;
    emit doneChanged(m_done);
}

void State::cancel()
{
    m_socket->write("cancel");
    done();
}

void State::tryAgain(int n)
{
    m_socket->write(QString("try_again %1").arg(n).toLocal8Bit());
    done();
}
