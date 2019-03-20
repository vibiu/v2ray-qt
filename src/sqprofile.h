#ifndef SQPROFILE_H
#define SQPROFILE_H

#include <QDataStream>
#include <QDate>
#include <QDateTime>

struct SQProfile 
{
    SQProfile();
    SQProfile(const QString& uri);

    bool autoStart;
    bool debug;
    quint16 serverPort;
    quint16 localPort;
    QString name;
    QString serverAddress;
    QString localAddress;
    QString method;
    QString password;
    QString dataPath;
    int timeout;
    int latency;
    quint64 cureentUsage;
    quint64 totalUsage;
    QDateTime lastTime;
    QDate nextResetDate;
    bool httpMode;

    static const int LATENCY_TIMEOUT = -1;
    static const int LATENCY_ERROR = -2;
    static const int LATENCY_UNKNOWN = -3;
};

Q_DECLARE_METATYPE(SQProfile)

#endif  // SQPROFILE_H
