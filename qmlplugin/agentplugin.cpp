/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "agentplugin.hpp"
#include "listener.hpp"

#include <agent.hpp>
#include <state.hpp>

void AgentPlugin::registerTypes(const char *uri) {
  Q_ASSERT(uri == QLatin1String("Agent"));

  qRegisterMetaType<State::ID>("StateID");

  qmlRegisterType<Agent>(uri, 1, 0, "Agent");
  qmlRegisterType<StateChange>(uri, 1, 0, "StateChange");
}
