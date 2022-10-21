/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include <QCoreApplication>
#include <UpdateHubListener>

void downloadCallback(Handler *handler) {
  qInfo("function called when starting the Download state;");
  qInfo("it will cancel the transition");

  handler->cancel();
}

void prepareLocalInstallCallback(Handler *handler) {
  qInfo("function called when starting the PrepareLocalInstall state");

  handler->proceed();
}

void installCallback(Handler *handler) {
  qInfo("function called when starting the Install state");

  handler->proceed();
}

void rebootCallback(Handler *handler) {
  qInfo("function called when starting the Reboot state");

  handler->done();
  exit(0);
}

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  StateChange listener;

  listener.onState(State::Download, downloadCallback);
  listener.onState(State::PrepareLocalInstall, prepareLocalInstallCallback);
  listener.onState(State::Install, installCallback);
  listener.onState(State::Reboot, rebootCallback);

  listener.listen();

  return app.exec();
}
