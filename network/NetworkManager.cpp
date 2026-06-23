#include "NetworkManager.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    connect(&m_server, &QTcpServer::newConnection,
            this, &NetworkManager::onNewConnection);
}

bool NetworkManager::connected() const
{
    return m_connected;
}

QString NetworkManager::statusText() const
{
    return m_statusText;
}

bool NetworkManager::isHost() const
{
    return m_isHost;
}

void NetworkManager::hostRoom(quint16 port)
{
    disconnectFromRoom();

    m_isHost = true;
    emit roleChanged();

    if (!m_server.listen(QHostAddress::AnyIPv4, port)) {
        setStatusText(QStringLiteral("创建房间失败"));
        return;
    }

    setStatusText(QStringLiteral("等待对方加入，端口 %1").arg(port));
}

void NetworkManager::joinRoom(const QString &ip, quint16 port)
{
    disconnectFromRoom();

    m_isHost = false;
    emit roleChanged();

    auto *socket = new QTcpSocket(this);
    setSocket(socket);

    setStatusText(QStringLiteral("连接中..."));
    socket->connectToHost(ip, port);

    connect(socket, &QTcpSocket::connected, this, [this]() {
        setConnected(true);
        setStatusText(QStringLiteral("已连接"));
    });
}

void NetworkManager::disconnectFromRoom()
{
    if (m_server.isListening()) {
        m_server.close();
    }

    if (m_socket) {
        m_socket->disconnectFromHost();
        m_socket->deleteLater();
        m_socket = nullptr;
    }

    setConnected(false);
    setStatusText(QStringLiteral("未连接"));
}

void NetworkManager::sendMove(int fromRow, int fromCol, int toRow, int toCol, QString nextTurn)
{
    QJsonObject object;
    object["type"] = "move";
    object["fromRow"] = fromRow;
    object["fromCol"] = fromCol;
    object["toRow"] = toRow;
    object["toCol"] = toCol;
    object["nextTurn"] = nextTurn;

    sendJson(object);
}

void NetworkManager::onNewConnection()
{
    if (m_socket) {
        QTcpSocket *extraSocket = m_server.nextPendingConnection();
        extraSocket->disconnectFromHost();
        extraSocket->deleteLater();
        return;
    }

    setSocket(m_server.nextPendingConnection());
    setConnected(true);
    setStatusText(QStringLiteral("已连接"));
}

void NetworkManager::onReadyRead()
{
    if (!m_socket) {
        return;
    }

    while (m_socket->canReadLine()) {
        const QByteArray line = m_socket->readLine().trimmed();
        const QJsonDocument document = QJsonDocument::fromJson(line);

        if (!document.isObject()) {
            continue;
        }

        const QJsonObject object = document.object();
        const QString type = object["type"].toString();

        if (type == "move") {
            emit moveReceived(
                object["fromRow"].toInt(),
                object["fromCol"].toInt(),
                object["toRow"].toInt(),
                object["toCol"].toInt(),
                object["nextTurn"].toString()
                );
        }
    }
}

void NetworkManager::onDisconnected()
{
    setConnected(false);
    setStatusText(QStringLiteral("连接已断开"));

    if (m_socket) {
        m_socket->deleteLater();
        m_socket = nullptr;
    }
}

void NetworkManager::setSocket(QTcpSocket *socket)
{
    if (m_socket && m_socket != socket) {
        m_socket->deleteLater();
    }

    m_socket = socket;

    connect(m_socket, &QTcpSocket::readyRead,
            this, &NetworkManager::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected,
            this, &NetworkManager::onDisconnected);
    connect(m_socket, &QTcpSocket::errorOccurred,
            this, [this]() {
                setStatusText(QStringLiteral("连接失败或已断开"));
            });
}

void NetworkManager::setStatusText(const QString &text)
{
    if (m_statusText == text) {
        return;
    }

    m_statusText = text;
    emit statusTextChanged();
}

void NetworkManager::setConnected(bool connected)
{
    if (m_connected == connected) {
        return;
    }

    m_connected = connected;
    emit connectedChanged();
}

void NetworkManager::sendJson(const QJsonObject &object)
{
    if (!m_socket || m_socket->state() != QAbstractSocket::ConnectedState) {
        return;
    }

    const QByteArray data = QJsonDocument(object).toJson(QJsonDocument::Compact) + '\n';
    m_socket->write(data);
    m_socket->flush();
}
