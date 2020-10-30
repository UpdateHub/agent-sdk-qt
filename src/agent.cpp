/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "agent.hpp"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

Agent::Agent(QObject *parent) : QObject(parent) {}

QVariantMap Agent::probe(const QString &serverAddress, bool ignoreProbeASAP) {
  return doProbe(serverAddress, ignoreProbeASAP);
}

QVariantMap Agent::info() {
  QNetworkAccessManager http;
  QNetworkRequest req(QUrl(QString("http://%1:%2/info")
                               .arg(m_defaultHost.host())
                               .arg(m_defaultHost.port())));

  QNetworkReply *reply = http.get(req);

  QEventLoop loop;
  connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  if (reply->error() != QNetworkReply::NoError) {
    qWarning() << reply->errorString();
    return QVariantMap();
  }

  QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

  return document.toVariant().toMap();
}

QVariantMap Agent::logs() {
  QNetworkAccessManager http;
  QNetworkRequest req(QUrl(QString("http://%1:%2/log")
                               .arg(m_defaultHost.host())
                               .arg(m_defaultHost.port())));

  QNetworkReply *reply = http.get(req);

  QEventLoop loop;
  connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  if (reply->error() != QNetworkReply::NoError) {
    qWarning() << reply->errorString();
    return QVariantMap();
  }

  QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

  return document.toVariant().toMap();
}

QVariantMap Agent::doProbe(const QString &serverAddress, bool ignoreProbeASAP) {
  QNetworkAccessManager http;
  QNetworkRequest req(QUrl(QString("http://%1:%2/probe")
                               .arg(m_defaultHost.host())
                               .arg(m_defaultHost.port())));
  req.setRawHeader("Content-Type", "application/json");

  QJsonObject json;
  json.insert("server-address", serverAddress);
  json.insert("ignore-probe-asap", ignoreProbeASAP);

  QNetworkReply *reply = http.post(req, QJsonDocument(json).toJson());

  QEventLoop loop;
  connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  if (reply->error() != QNetworkReply::NoError) {
    qWarning() << reply->errorString();
    return QVariantMap();
  }

  QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

  return document.toVariant().toMap();
}
