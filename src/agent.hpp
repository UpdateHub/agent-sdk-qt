/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>

class Agent : public QObject {
  Q_OBJECT public : Agent(QObject *parent = NULL);

  inline void setDefaultHost(const QUrl &host) { this->m_defaultHost = host; };

public slots:
  QByteArray info();
  QByteArray log();
  QByteArray abortDownload();
  QByteArray localInstall(const QString &file);
  QByteArray remoteInstall(const QString &url);
  QByteArray probe(const QString &serverAddress);

private:
  QUrl m_defaultHost = QUrl("http://localhost:8080");

  QByteArray processRequest(const QString &route, QJsonObject json);
};

#endif // AGENT_HPP
