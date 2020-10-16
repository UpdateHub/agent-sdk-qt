/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "handler.hpp"
#include "state.hpp"

#include <QDir>
#include <QFile>
#include <QHash>
#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>
#include <QVector>

typedef std::function<void(Handler *)> CallbackFunc;
typedef QHash<QString, QVector<CallbackFunc>> CallbacksMap;

class StateChange : public QObject {
  Q_OBJECT public : StateChange(QObject *parent = NULL);

public:
  void listen();
  void onState(State::ID, CallbackFunc);

private:
  const char *SOCKET_PATH = "/run/updatehub-statechange.sock";
  const char *SDK_TRIGGER_FILENAME =
      "/usr/share/updatehub/state-change-callbacks.d/"
      "10-updatehub-sdk-statechange-trigger";

  CallbacksMap m_callbacks;
  QLocalServer *m_server;

  void emitCallback(QLocalSocket *socket, const QString &input);
  void handleConnection(QLocalSocket *socket, const QByteArray &data);
  void checkSocket();
};

inline const QString toQString(State::ID state) {
  switch (state) {
  case State::Probe:
    return QString("probe");
  case State::Download:
    return QString("download");
  case State::Install:
    return QString("install");
  case State::Reboot:
    return QString("reboot");
  case State::Error:
    return QString("error");
  default:
    return QString("invalid");
  }
}

#endif // LISTENER_HPP
