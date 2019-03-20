#include "confighelper.h"

ConfigHelper::ConfigHelper(QObject *parent) :
    QObject(parent),
    m_mode(2),
    m_enable(true),
    m_running(true),
    m_isHideWindowOnStartup(true),
    m_localPort(1090),
    m_pacPort(1070),
    m_dataPath(QString("data"))
{}

bool ConfigHelper::isHideWindowOnStartup() const
{
    return m_isHideWindowOnStartup;
}

bool ConfigHelper::enable() const
{
    return m_enable;
}

bool ConfigHelper::running() const
{
    return m_running;
}

int ConfigHelper::mode() const
{
    return m_mode;
}

int ConfigHelper::localPort() const
{
    return m_localPort;
}

int ConfigHelper::pacPort() const
{
    return m_pacPort;
}

QString ConfigHelper::dataPath() const
{
    return m_dataPath;
}

void ConfigHelper::setEnable(bool isEnable)
{
    m_enable = isEnable;
}

void ConfigHelper::setRunning(bool isRunning)
{
    m_running = isRunning;
}

void ConfigHelper::setMode(int iMode)
{
    m_mode = iMode;
}

void ConfigHelper::setLocalPort(int iLocalPort)
{
    m_localPort = iLocalPort;
}

void ConfigHelper::setPacPort(int iPacPort)
{
    m_pacPort = iPacPort;
}

void ConfigHelper::setDataPath(QString sDataPath)
{
	m_dataPath = sDataPath;
}
