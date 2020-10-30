/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#include "agentplugin.hpp"
#include "statechangelistener.hpp"

#include <agent.hpp>
#include <state.hpp>

void AgentPlugin::registerTypes(const char *uri) {
  Q_ASSERT(uri == QLatin1String("Agent"));

  qRegisterMetaType<StateChangeListener::Action>("Action");
  qRegisterMetaType<State::ID>("StateID");

  qmlRegisterType<Agent>(uri, 1, 0, "Agent");
  qmlRegisterType<StateChangeListener>(uri, 1, 0, "StateChangeListener");
  qmlRegisterType<State>(uri, 1, 0, "AgentState");
}
