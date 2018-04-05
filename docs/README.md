## class ```Agent```

### Methods

#### ```probe(const QString &serverAddress = "")```

Probe updatehub agent for update

#### ```getInfo()```

Get updatehub agent general information

#### ```getLogs()```

Get updatehub agent log entries

## class ```StateChangeListener```

### Methods

#### ```listen()```

Listen for state changes of updatehub agent

### Signals

#### ```stateChanged(Action action, State *state)```

This signal is emitted when the state has been changed

### class ```State```

### Methods

#### ```id()```

Get state id

#### ```tryAgain(int n)```

Try again state in *n* seconds

#### ```cancel()```

Cancel state
