/*
 * updatehub
 * Copyright (C) 2018-2020
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#ifndef STATE_HPP
#define STATE_HPP

class State {
public:
  enum ID { Invalid, Probe, Download, PrepareLocalInstall, Install, Reboot, Error };
  ID id;
};

inline State::ID toState(const QString &input) {
  if (input.contains("probe"))
    return State::Probe;
  if (input.contains("download"))
    return State::Download;
  if (input.contains("prepare_local_install"))
    return State::PrepareLocalInstall;
  if (input.contains("install"))
    return State::Install;
  if (input.contains("reboot"))
    return State::Reboot;
  if (input.contains("error"))
    return State::Error;

  return State::Invalid;
}

#endif // STATE_HPP
