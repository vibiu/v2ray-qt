#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTCore>
#include "controller.h"

class HttpServer : public QObject
{
    Q_OBJECT

public:
    explicit HttpServer(QHostAddress address, int port, QObject *parent=nullptr);
    ~HttpServer();

    bool listen();

    void close();

private slots:
    void newConnection();

private:
    int port;
    QHostAddress address;
    QTcpServer *tcpServer;
};

#endif  // HTTPSERVER_H
