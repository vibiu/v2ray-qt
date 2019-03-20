#include "sqprofile.h"

SQProfile::SQProfile()
{
    autoStart = false;
    debug = false;
    serverPort = 1090;
    localPort = 1090;
    name = QObject::tr("Unnamed Profile");
    localAddress = QString("127.0.0.1");
    method = QString("RC4-MD5");
    timeout = 600;
    latency = LATENCY_UNKNOWN;
    cureentUsage = 0;
    totalUsage = 0;
    QDate currentDate = QDate::currentDate();
    nextResetDate = QDate(currentDate.year(), currentDate.month() + 1, 1);
    httpMode = false;
    dataPath = "data";
}

SQProfile::SQProfile(const QString &uri): SQProfile()
{
    // TODO: suport SIP002 URI Scheme
}

