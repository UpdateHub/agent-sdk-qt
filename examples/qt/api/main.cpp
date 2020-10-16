/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include <QCoreApplication>
#include <UpdateHubAgent>

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  Agent agent;

  QByteArray info = agent.info();

  qInfo() << qPrintable(info) << "\n\n";

  QByteArray log = agent.log();

  qInfo() << qPrintable(log) << "\n\n";

  QByteArray probe = agent.probe("");

  qInfo() << qPrintable(probe) << "\n\n";

  QByteArray probeCustom = agent.probe("http://www.example.com:8080");

  qInfo() << qPrintable(probeCustom) << "\n\n";

  QByteArray localInstall = agent.localInstall("/tmp/update.uhu");

  qInfo() << qPrintable(localInstall) << "\n\n";

  QByteArray remoteInstall = agent.remoteInstall("http://www.example.com:8080");

  qInfo() << qPrintable(remoteInstall) << "\n\n";
}
