## class ```Agent```

### Methods

#### ```probe(const QString &serverAddress)```

Probe the agent for update.

#### ```info()```

Get the current state of the agent.

#### ```log()```

Get the available log entries for the last update cycle.

#### ```localInstall(const QString &file)```

Request agent to install a local update package.

#### ```remoteInstall(const QString &url)```

Request agent to install a package from a URL.

#### ```abortDownload()```

Tells agent to abort the current download.

## class ```StateChange```

### Methods

#### ```listen()```

Listen for state changes of updatehub agent.

### ```onState(State::ID, callback)```

Register the callbacks for a state.

### class ```Handler```

### Methods

#### ```cancel()```

Cancel the current action on the agent.

#### ```proceed()```

Tell the agent to proceed with the transition.
