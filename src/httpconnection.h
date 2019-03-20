#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H
#include <QObject>
#include <QTcpSocket>
#include <QByteArray>


class HttpConnection: public QObject
{
    Q_OBJECT

public:
    HttpConnection(QTcpSocket *socket, QObject *parent=nullptr);
    ~HttpConnection();

private slots:
    void handleRequst();

private:
    QTcpSocket *socket;
    QByteArray *socketBuffer;
};

#endif  // HTTP_CONNECTION_H
