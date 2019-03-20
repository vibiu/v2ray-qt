#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QSettings>

class MainWindow;

class Connection: public QObject
{
    Q_OBJECT

public:
    Connection(MainWindow *w, QObject *parent=0);
    ~Connection();

    void disableProxy();

    void setPacMode();

    void setGlobalMode();

private:
    MainWindow *window;
};


#endif  // CONNECTION_H
