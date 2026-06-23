#pragma once

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>

class NetworkManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(bool isHost READ isHost NOTIFY roleChanged)

public:
    explicit NetworkManager(QObject *parent = nullptr);

    bool connected() const;
    QString statusText() const;
    bool isHost() const;

    Q_INVOKABLE void hostRoom(quint16 port = 45454);
    Q_INVOKABLE void joinRoom(const QString &ip, quint16 port = 45454);
    Q_INVOKABLE void disconnectFromRoom();

    Q_INVOKABLE void sendMove(int fromX,
                              int fromY,
                              int toX,
                              int toY);

signals:
    void connectedChanged();
    void statusTextChanged();
    void roleChanged();

    void moveReceived(int fromX,
                      int fromY,
                      int toX,
                      int toY);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    void setSocket(QTcpSocket *socket);
    void setStatusText(const QString &text);
    void setConnected(bool connected);
    void sendJson(const QJsonObject &object);

private:
    QTcpServer m_server;
    QTcpSocket *m_socket = nullptr;

    bool m_connected = false;
    bool m_isHost = false;

    QString m_statusText = QStringLiteral("未连接");
};
