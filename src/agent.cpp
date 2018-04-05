/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "agent.hpp"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

Agent::Agent(QObject *parent): QObject(parent)
{
}

QVariantMap Agent::probe(const QString &serverAddress)
{
    return doProbe(serverAddress);
}

QVariantMap Agent::info()
{
    QNetworkAccessManager http;
    QNetworkRequest req(QUrl("http://localhost:8080/info"));

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

QVariantMap Agent::logs()
{
    QNetworkAccessManager http;
    QNetworkRequest req(QUrl("http://localhost:8080/log"));

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

QVariantMap Agent::doProbe(const QString &serverAddress)
{
    QNetworkAccessManager http;
    QNetworkRequest req(QUrl("http://localhost:8080/probe"));
    req.setRawHeader("Content-Type", "application/json");

    QJsonObject json;
    json.insert("server-address", serverAddress);

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
