#include <QDebug>
#include <QByteArray>
#include "httpserver.h"
#include "httpconnection.h"



HttpServer::HttpServer(QHostAddress address, int port, QObject *parent):
    QObject(parent),
    address(address),
    port(port)
{
}

HttpServer::~HttpServer()
{
}

bool HttpServer::listen()
{
    tcpServer = new QTcpServer(this);

    bool listenSucess = tcpServer->listen(address, port);
    if (listenSucess) {
        connect(tcpServer, &QTcpServer::newConnection, this, &HttpServer::newConnection);
    } else {
        delete tcpServer;
        tcpServer = nullptr;
    }
    return listenSucess;
}

void HttpServer::close()
{
    if (tcpServer) {
        tcpServer->close();
    }
}


void HttpServer::newConnection()
{
    Q_ASSERT(tcpServer);

    HttpConnection *httpConnection = new HttpConnection(
        tcpServer->nextPendingConnection(), this);
}
