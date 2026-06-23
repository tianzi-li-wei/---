#include "NetworkManager.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QTimer>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    connect(&m_server,
            &QTcpServer::newConnection,
            this,
            &NetworkManager::onNewConnection);
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

    if (!m_server.listen(QHostAddress::AnyIPv4, port))
    {
        setConnected(false);
        setStatusText(QStringLiteral("创建房间失败：%1")
                          .arg(m_server.errorString()));
        return;
    }

    setConnected(false);
    setStatusText(QStringLiteral("等待对方加入，端口 %1").arg(port));
}

void NetworkManager::joinRoom(const QString &ip, quint16 port)
{
    QString trimmedIp = ip.trimmed();

    if (trimmedIp.isEmpty())
    {
        setStatusText(QStringLiteral("请输入 IP 地址"));
        return;
    }

    disconnectFromRoom();

    m_isHost = false;
    emit roleChanged();

    QTcpSocket *socket = new QTcpSocket(this);
    setSocket(socket);

    connect(socket,
            &QTcpSocket::connected,
            this,
            [this]() {
                setConnected(true);
                setStatusText(QStringLiteral("已连接"));
            });

    setStatusText(QStringLiteral("正在连接 %1:%2")
                      .arg(trimmedIp)
                      .arg(port));

    socket->connectToHost(trimmedIp, port);

    QTimer::singleShot(5000, this, [this, socket]() {
        if (m_socket == socket &&
            socket->state() != QAbstractSocket::ConnectedState)
        {
            socket->abort();
            setConnected(false);
            setStatusText(QStringLiteral("连接超时"));
        }
    });
}

void NetworkManager::disconnectFromRoom()
{
    if (m_server.isListening())
    {
        m_server.close();
    }

    if (m_socket)
    {
        QTcpSocket *oldSocket = m_socket;
        m_socket = nullptr;

        oldSocket->disconnectFromHost();
        oldSocket->deleteLater();
    }

    m_isHost = false;
    emit roleChanged();

    setConnected(false);
    setStatusText(QStringLiteral("未连接"));
}

void NetworkManager::sendMove(int fromX,
                              int fromY,
                              int toX,
                              int toY)
{
    QJsonObject object;

    object["type"] = "move";
    object["fromX"] = fromX;
    object["fromY"] = fromY;
    object["toX"] = toX;
    object["toY"] = toY;

    sendJson(object);
}

void NetworkManager::onNewConnection()
{
    if (m_socket)
    {
        QTcpSocket *extraSocket = m_server.nextPendingConnection();

        extraSocket->disconnectFromHost();
        extraSocket->deleteLater();

        return;
    }

    QTcpSocket *socket = m_server.nextPendingConnection();

    setSocket(socket);
    setConnected(true);
    setStatusText(QStringLiteral("已连接"));
}

void NetworkManager::onReadyRead()
{
    if (!m_socket)
    {
        return;
    }

    while (m_socket->canReadLine())
    {
        QByteArray line = m_socket->readLine().trimmed();

        QJsonDocument document =
            QJsonDocument::fromJson(line);

        if (!document.isObject())
        {
            continue;
        }

        QJsonObject object = document.object();
        QString type = object["type"].toString();

        if (type == "move")
        {
            emit moveReceived(
                object["fromX"].toInt(),
                object["fromY"].toInt(),
                object["toX"].toInt(),
                object["toY"].toInt());
        }
    }
}

void NetworkManager::onDisconnected()
{
    setConnected(false);
    setStatusText(QStringLiteral("连接已断开"));

    if (m_socket)
    {
        m_socket->deleteLater();
        m_socket = nullptr;
    }
}

void NetworkManager::setSocket(QTcpSocket *socket)
{
    if (m_socket && m_socket != socket)
    {
        m_socket->deleteLater();
    }

    m_socket = socket;

    connect(m_socket,
            &QTcpSocket::readyRead,
            this,
            &NetworkManager::onReadyRead);

    connect(m_socket,
            &QTcpSocket::disconnected,
            this,
            &NetworkManager::onDisconnected);

    connect(m_socket,
            &QTcpSocket::errorOccurred,
            this,
            [this](QAbstractSocket::SocketError) {
                setConnected(false);
                setStatusText(QStringLiteral("连接失败或已断开"));
            });
}

void NetworkManager::setStatusText(const QString &text)
{
    if (m_statusText == text)
    {
        return;
    }

    m_statusText = text;
    emit statusTextChanged();
}

void NetworkManager::setConnected(bool connected)
{
    if (m_connected == connected)
    {
        return;
    }

    m_connected = connected;
    emit connectedChanged();
}

void NetworkManager::sendJson(const QJsonObject &object)
{
    if (!m_socket ||
        m_socket->state() != QAbstractSocket::ConnectedState)
    {
        return;
    }

    QByteArray data =
        QJsonDocument(object).toJson(QJsonDocument::Compact);

    data.append('\n');

    m_socket->write(data);
    m_socket->flush();
}
