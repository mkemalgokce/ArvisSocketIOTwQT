//
// Created by mkg on 07.06.2023.
//

#include "websocketserver.h"

WebSocketServer::WebSocketServer() {
    _port = 12345;
    _server = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);
    connect(_server, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
    connect(_server, &QWebSocketServer::closed, this, &WebSocketServer::onClosed);


    if(!_server->listen(QHostAddress::Any, _port)) {
        qFatal("Failed to start websocket server !");
    }
    qInfo("Websocket server started on: %d.", _port);
}

WebSocketServer::~WebSocketServer() {
    _server->close();
    qDeleteAll(_clients);
}

void WebSocketServer::onNewConnection() {
    QWebSocket *clientSocket = _server->nextPendingConnection();
    connect(clientSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
    connect(clientSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

    _clients.append(clientSocket);

    qDebug() << "Client connected:" << clientSocket->peerAddress().toString();
}

void WebSocketServer::onClosed() {
    qDebug() << "WebSocket server closed";
    qDeleteAll(_clients);
}

void WebSocketServer::onTextMessageReceived(const QString &message) {
    auto *clientSocket = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Message received:" << message;
    QJsonObject jsonObj = QJsonDocument::fromJson(message.toUtf8()).object();
    if(jsonObj.count() == 2 && !jsonObj["command"].isNull() && !jsonObj["sender"].isNull() ) {
        auto command =  jsonObj["command"].toString();
        emit(commandCame(command));
        clientSocket->close();
    }
}

void WebSocketServer::socketDisconnected() {
    auto *clientSocket = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();

    _clients.removeOne(clientSocket);
    clientSocket->deleteLater();
}

void WebSocketServer::onOpened() {

}
