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

  qInfo() << qPrintable(agent.info()) << "\n\n";
  qInfo() << qPrintable(agent.log()) << "\n\n";
  qInfo() << qPrintable(agent.probe("")) << "\n\n";
  qInfo() << qPrintable(agent.probe("http://www.example.com:8080")) << "\n\n";
  qInfo() << qPrintable(agent.localInstall("/tmp/update.uhu")) << "\n\n";
  qInfo() << qPrintable(agent.remoteInstall("http://www.example.com:8080"))
          << "\n\n";
}
