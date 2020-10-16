/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "handler.hpp"

Handler::Handler() : QObject() {}

void Handler::setSocket(QLocalSocket *socket) { this->m_socket = socket; };

void Handler::done() {
  this->m_socket->close();
  this->m_done = true;
  emit doneChanged(this->m_done);
}

void Handler::cancel() {
  this->m_socket->write("cancel");
  done();
}

void Handler::proceed() {}
