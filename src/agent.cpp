/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "agent.hpp"

Agent::Agent(QObject *parent) : QObject(parent) {}

QByteArray Agent::info() {
  return this->processRequest(QString("info"), QJsonObject());
}

QByteArray Agent::log() {
  return this->processRequest(QString("log"), QJsonObject());
}

QByteArray Agent::probe(const QString &serverAddress) {
  QJsonObject json;
  json.insert("custom_server", serverAddress);

  return this->processRequest(QString("probe"), json);
}

QByteArray Agent::localInstall(const QString &file) {
  QJsonObject json;
  json.insert("file", file);

  return this->processRequest(QString("local_install"), json);
}

QByteArray Agent::remoteInstall(const QString &url) {
  QJsonObject json;
  json.insert("url", url);

  return this->processRequest(QString("remote_install"), json);
}

QByteArray Agent::abortDownload() {
  return this->processRequest(QString("update/download/abort"), QJsonObject());
}

QByteArray Agent::processRequest(const QString &route, QJsonObject json) {
  QNetworkAccessManager http;
  QNetworkReply *reply;
  QNetworkRequest req(QUrl(QString("http://%1:%2/%3")
                               .arg(this->m_defaultHost.host())
                               .arg(this->m_defaultHost.port())
                               .arg(route)));

  if (json.isEmpty()) {
    reply = http.get(req);
  } else {
    req.setRawHeader("Content-Type", "application/json");
    reply = http.post(req, QJsonDocument(json).toJson());
  }

  QEventLoop loop;
  connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  if (reply->error() != QNetworkReply::NoError) {
    qWarning() << reply->errorString();
    return QByteArray();
  }

  return reply->readAll();
}
