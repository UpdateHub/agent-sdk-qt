/*
 * updatehub
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     MIT
 */

#ifndef STATE_HPP
#define STATE_HPP

#include <QObject>

class QLocalSocket;

class State: public QObject
{
    Q_OBJECT
    Q_PROPERTY(ID Id READ id)
    Q_PROPERTY(bool IsDone READ isDone NOTIFY doneChanged)

public:
    enum ID {
        Invalid = 0,
        Idle,
        Poll,
        Probe,
        Downloading,
        Downloaded,
        Installing,
        Installed,
        Exit,
        Error,
        Rebooting
    };

    Q_ENUM(ID)

    State();
    State(ID id, QLocalSocket *socket, QObject *parent = NULL);

public slots:
    inline ID id() const { return m_id; }
    inline bool isDone() const { return m_done; }

    void done();
    void cancel();
    void tryAgain(int n);

signals:
    void doneChanged(bool done);

private:
    ID m_id;
    QLocalSocket *m_socket;
    bool m_done;
};

#endif // STATE_HPP
