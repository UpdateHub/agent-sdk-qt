/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "listener.hpp"
#include "handler.hpp"
#include "state.hpp"

StateChange::StateChange(QObject *parent) : QObject(parent) {
  this->m_server = new QLocalServer;

  if (!QFile::exists(SDK_TRIGGER_FILENAME)) {
    qWarning("WARNING: updatehub-sdk-statechange-trigger not found on %s",
             SDK_TRIGGER_FILENAME);
  }
}

void StateChange::listen() {
  this->checkSocket();

  connect(this->m_server, &QLocalServer::newConnection, [=]() {
    QLocalSocket *socket = this->m_server->nextPendingConnection();
    connect(socket, &QLocalSocket::disconnected,
            [=]() { socket->deleteLater(); });
    connect(socket, &QLocalSocket::readyRead,
            [=]() { this->handleConnection(socket, socket->readAll()); });
  });
}

void StateChange::onState(State::ID state, CallbackFunc f) {
  this->m_callbacks[toQString(state)].push_back(f);
}

void StateChange::handleConnection(QLocalSocket *socket,
                                   const QByteArray &data) {
  QStringList lines = QString::fromLocal8Bit(data).split('\n');

  foreach (const QString &line, lines) {
    if (line.isEmpty())
      continue;

    auto *handler = new Handler(socket, this);

    this->emitCallback(socket, line);

    if (QObject::receivers(SIGNAL(doneChanged(Handler *))) == 0)
      handler->done();
  }
}

void StateChange::emitCallback(QLocalSocket *socket, const QString &input) {
  for (auto const &f : this->m_callbacks[input]) {
    f(new Handler(socket, this));
  }
}

void StateChange::checkSocket() {
  QString socket;
  QString abs_dir = QDir::currentPath() + "/";

  auto env_p = qgetenv("UH_LISTENER_TEST");
  auto str_env_p(env_p);

  if (!str_env_p.isEmpty()) {
    socket = env_p;
  } else {
    socket = SOCKET_PATH;
  }

  abs_dir.append(socket);

  if (QFile::exists(abs_dir))
    QLocalServer::removeServer(abs_dir);

  this->m_server->close();
  this->m_server->listen(abs_dir);
}
