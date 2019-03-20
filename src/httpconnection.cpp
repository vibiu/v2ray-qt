#include <QDir>
#include <QFile>
#include <QDateTime>
#include <Qlocale>
#include "httpconnection.h"

HttpConnection::HttpConnection(QTcpSocket *socket, QObject *parent):
    QObject(parent),
    socket(socket)
{
    socketBuffer = new QByteArray();
    connect(socket, &QTcpSocket::readyRead, this, &HttpConnection::handleRequst);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

HttpConnection::~HttpConnection()
{
    if (socketBuffer) {
        delete socketBuffer;
        socketBuffer = nullptr;
    }
}

void HttpConnection::handleRequst()
{
    while (socket->bytesAvailable()) {
        QByteArray arr = socket->readAll();
        socketBuffer->append(arr);
    }
    qDebug() << "recieve message:";
    qDebug() << QString::fromStdString(socketBuffer->toStdString());

    QString currentPath = QDir::currentPath();
    QString pacPath = currentPath + "/data/v2ray/pac";
    QFile pacFile(pacPath);

    QByteArray pacContent;
    int status = 200;
    
    if (!pacFile.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {
        status = 404;
        pacContent = "<h1>404 Not Found</h1>";
    } else {
        pacContent = pacFile.readAll();
    }
    pacFile.close();

    QDateTime now = QDateTime::currentDateTime();
    QString currentDate = "Date: " + QLocale{QLocale::English}.toString(
        now, "ddd, dd MMM yyyy HH:mm:ss") + " GMT\r\n";

    QString lens(QString::number(pacContent.length()));
    QString contentLength("Content-Length: " + lens + "\r\n\r\n");
    if (status == 200) {
        socket->write("HTTP/1.0 200 OK\r\n");
        socket->write("Server: v2ray-qt5\r\n");
        socket->write("Content-Type: application/octet-stream\r\n");
        socket->write("Content-Disposition: attachment; filename=pac\r\n");
        socket->write(currentDate.toLatin1());
        socket->write(contentLength.toLatin1());
        socket->write(pacContent);
        socket->flush();
    } else {
        socket->write("HTTP/1.0 404 NOT FOUND\r\n");
        socket->write("Server: v2ray-qt5\r\n");
        socket->write("Content-Type: text/html; charset=utf-8\r\n");
        socket->write(currentDate.toLatin1());
        socket->write(contentLength.toLatin1());
        socket->write(pacContent);
        socket->flush();
    }

    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    socket->disconnectFromHost();
}
