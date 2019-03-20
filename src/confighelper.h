#ifndef CONFIGHELPER_H
#define CONFIGHELPER_H

#include <QObject>

class ConfigHelper: public QObject
{
    Q_OBJECT

public:
    explicit ConfigHelper(QObject *parent = nullptr);

    bool isHideWindowOnStartup() const;
    bool enable() const;
    bool running() const;
    int mode() const;
    int localPort() const;
    int pacPort() const;
    QString dataPath() const;

    void setEnable(bool isEnable);
    void setRunning(bool isRunning);
    void setMode(int iMode);
    void setLocalPort(int iLocalPort);
    void setPacPort(int iPacPort);
    void setDataPath(QString sDataPath);

private:
    bool m_isHideWindowOnStartup;
    bool m_enable;
    bool m_running;
    int m_mode; // 1-global, 2-pac, 3-direct
    int m_localPort;
    int m_pacPort;
    QString m_dataPath;
};

#endif  // CONFIGHELPER_H
