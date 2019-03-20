#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QProcess>
#include "sqprofile.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(SQProfile *_profile, QObject *parent=nullptr);
    ~Controller();

    void start();

    void close();

private slots:
    void processError(QProcess::ProcessError error);

private:
    int name;
    SQProfile *profile;
    QProcess *v2rayProcess;
};

#endif  // CONTROLLER_H
