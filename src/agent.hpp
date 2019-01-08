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

class Agent: public QObject
{
    Q_OBJECT

public:
    Agent(QObject *parent = NULL);

public slots:
    QVariantMap probe(const QString &serverAddress, bool ignoreProbeASAP = false);
    QVariantMap info();
    QVariantMap logs();

private:
    QVariantMap doProbe(const QString &serverAddress, bool ignoreProbeASAP);
};

#endif // AGENT_HPP
