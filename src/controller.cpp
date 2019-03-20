#include <QDebug>
#include <QDir>
#include "controller.h"

Controller::Controller(SQProfile *_profile, QObject *parent) : 
    QObject(parent)
{
    profile = _profile;
    v2rayProcess = new QProcess(this);

    connect(v2rayProcess, &QProcess::errorOccurred, this, &Controller::processError);
    qDebug("controller set up");
    start();
}

Controller::~Controller()
{
    if (v2rayProcess) {
        v2rayProcess->close();
    }
    qDebug("controler teardown");
}

void Controller::start()
{
    QString currentPath = QDir::currentPath();
    QString program = tr("%1/%2/v2ray/v2ray.exe").arg(currentPath).arg(profile->dataPath);
    qDebug() << program;
    v2rayProcess->start(program);
}

void Controller::close()
{
    v2rayProcess->close();
}

void Controller::processError(QProcess::ProcessError error)
{
    qDebug() << "error occurs";
}
