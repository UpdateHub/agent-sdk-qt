/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <QObject>
#include <QVariantMap>
#include <QUrl>

class Agent: public QObject
{
    Q_OBJECT

public:
    Agent(QObject *parent = NULL);

    inline void setDefaultHost(const QUrl &host) { m_defaultHost = host; };

public slots:
    QVariantMap probe(const QString &serverAddress, bool ignoreProbeASAP = false);
    QVariantMap info();
    QVariantMap logs();

private:
    QUrl m_defaultHost = QUrl("tcp://localhost:8080");

    QVariantMap doProbe(const QString &serverAddress, bool ignoreProbeASAP);
};

#endif // AGENT_HPP
