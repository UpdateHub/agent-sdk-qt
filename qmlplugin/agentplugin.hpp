/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#ifndef AGENTPLUGIN_HPP
#define AGENTPLUGIN_HPP

#include <QQmlEngine>
#include <QQmlExtensionPlugin>

class AgentPlugin : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
  void registerTypes(const char *uri);
};

#endif // AGENTPLUGIN_HPP
