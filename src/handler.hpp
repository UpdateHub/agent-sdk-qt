/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <QLocalSocket>
#include <QObject>

class Handler : public QObject {
  Q_OBJECT public : Handler();

  Handler(QLocalSocket *socket, QObject *parent)
      : QObject(parent), m_done(false), m_socket(socket) {}

public slots:
  void done();
  void cancel();
  void proceed();
  void setSocket(QLocalSocket *socket);

signals:
  void doneChanged(bool done);

private:
  bool m_done;
  QLocalSocket *m_socket;
};

#endif // HANDLER_HPP
