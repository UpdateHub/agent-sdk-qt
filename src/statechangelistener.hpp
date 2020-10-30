/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#ifndef STATECHANGELISTENER_HPP
#define STATECHANGELISTENER_HPP

#include <QObject>

class QLocalServer;
class QLocalSocket;
class State;

class StateChangeListener : public QObject {
  Q_OBJECT public : StateChangeListener(QObject *parent = NULL);

  enum Action { ActionInvalid = 0, ActionEnter, ActionLeave };

  Q_ENUM(Action)
public slots:
  void listen();

signals:
  void stateChanged(Action action, State *state);
  void errorOccurred(const QString &error);

private:
  void parseData(QLocalSocket *socket, const QByteArray &data);

private:
  QLocalServer *m_server;
};

#endif // STATECHANGELISTENER_HPP
