//
// Created by mkg on 07.06.2023.
//

#ifndef ARVISIOTSERVER_WEBSOCKETSERVER_H
#define ARVISIOTSERVER_WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QJsonDocument>
#include <QJsonObject>

class WebSocketServer: public QObject {
    Q_OBJECT
public:
     WebSocketServer();
    ~WebSocketServer();

public slots:
    void onOpened();
    void onNewConnection();
    void onClosed();
    void onTextMessageReceived(const QString &message);
    void socketDisconnected();

signals:
    void commandCame(const QString);
private:
    QWebSocketServer* _server;
    QList<QWebSocket *> _clients;
    quint16 _port;

};


#endif //ARVISIOTSERVER_WEBSOCKETSERVER_H
