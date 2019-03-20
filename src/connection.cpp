#include <QDebug>
#include "mainwindow.h"
#include "connection.h"
#include <string>
#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib,"wininet.lib")

Connection::Connection(MainWindow *w, QObject *parent) :
    window(w),
    QObject(parent)
{
}

Connection::~Connection()
{
    disableProxy();
}

void Connection::disableProxy()
{
    const int optionCount = 1;
    INTERNET_PER_CONN_OPTION_LIST optionList;
    INTERNET_PER_CONN_OPTION optionsArr[optionCount];
    unsigned long optionListSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);

    optionsArr[0].dwOption = INTERNET_PER_CONN_FLAGS;
    optionsArr[0].Value.dwValue = 0;

    optionList.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
    optionList.pszConnection = NULL;
    optionList.dwOptionCount = optionCount;
    optionList.dwOptionError = 0;
    optionList.pOptions = optionsArr;

    InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &optionList, optionListSize);

    qDebug() << "disable proxy";
}


void Connection::setPacMode()
{
    const int optionCount = 3;
    INTERNET_PER_CONN_OPTION_LIST optionList;
    INTERNET_PER_CONN_OPTION optionsArr[optionCount];
    unsigned long optionListSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);

    optionsArr[0].dwOption = INTERNET_PER_CONN_FLAGS;
    optionsArr[0].Value.dwValue = 0;
    optionsArr[0].Value.dwValue |= PROXY_TYPE_AUTO_PROXY_URL;

    QString proxyServerStr = tr("127.0.0.1:%1").arg(
        window->configHelper->localPort());
    LPWSTR lpProxyServer = new wchar_t[proxyServerStr.length()+1];
    proxyServerStr.toWCharArray(lpProxyServer);
    lpProxyServer[proxyServerStr.length()] = '\0';

    QString autoConfigUrlStr = tr("http://127.0.0.1:%1/pac").arg(
        window->configHelper->pacPort());
    LPWSTR lpAutoConfigUrl = new wchar_t[autoConfigUrlStr.length()+1];
    autoConfigUrlStr.toWCharArray(lpAutoConfigUrl);
    lpAutoConfigUrl[autoConfigUrlStr.length()] = '\0';

    optionsArr[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
    optionsArr[1].Value.pszValue = lpProxyServer;

    optionsArr[2].dwOption = INTERNET_PER_CONN_AUTOCONFIG_URL;
    optionsArr[2].Value.pszValue = lpAutoConfigUrl;

    optionList.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
    optionList.pszConnection = NULL;
    optionList.dwOptionCount = optionCount;
    optionList.dwOptionError = 0;
    optionList.pOptions = optionsArr;

    InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &optionList, optionListSize);

    qDebug() << "set pac mode";
}

void Connection::setGlobalMode()
{
    const int optionCount = 2;
    INTERNET_PER_CONN_OPTION_LIST optionList;
    INTERNET_PER_CONN_OPTION optionsArr[optionCount];
    unsigned long optionListSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);

    optionsArr[0].dwOption = INTERNET_PER_CONN_FLAGS;
    optionsArr[0].Value.dwValue = 0;
    optionsArr[0].Value.dwValue |= PROXY_TYPE_PROXY;

    QString proxyServerStr = tr("127.0.0.1:%1").arg(
        window->configHelper->localPort());
    LPWSTR lpProxyServer = new wchar_t[proxyServerStr.length()+1];
    proxyServerStr.toWCharArray(lpProxyServer);
    lpProxyServer[proxyServerStr.length()] = '\0';

    optionsArr[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
    optionsArr[1].Value.pszValue = lpProxyServer;

    optionList.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
    optionList.pszConnection = NULL;
    optionList.dwOptionCount = optionCount;
    optionList.dwOptionError = 0;
    optionList.pOptions = optionsArr;

    InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &optionList, optionListSize);

    qDebug() << "set global mode";
}
