#include "mainwindow.h"
#include "statusnotifier.h"
#include <QApplication>

StatusNotifier::StatusNotifier(MainWindow *w, bool startHiden, QObject *parent) :
    QObject(parent),
    window(w)
{
    int mode = window->configHelper->mode();
    bool enable = window->configHelper->enable();

    systray.setIcon(QIcon(":/icons/icons/v2ray-qt5.png"));
    systray.setToolTip(QString("V2ray-Qt5"));
    connect(&systray, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason r) {
        if (r != QSystemTrayIcon::Context) {
            this->activate();
        }
    });

    minimiseRestoreAction = new QAction(startHiden ? tr("Restore"): tr("Minimise"), this);
    connect(minimiseRestoreAction, &QAction::triggered, this, &StatusNotifier::activate);

    
    enableDisableAction = new QAction(enable ? tr("Disable proxy"): tr("Enable proxy"));
    enableDisableAction->setCheckable(true);
    enableDisableAction->setChecked(enable);
    connect(enableDisableAction, &QAction::triggered, this, &StatusNotifier::onChangeProxy);

    
    changeModeMenu = new QMenu(tr("Proxy mode"));
    changeModeMenu->setEnabled(enable);
    pacModeAction = new QAction(tr("PAC mode"));
    pacModeAction->setCheckable(true);
    globalModeAction = new QAction(tr("Global mode"));
    globalModeAction->setCheckable(true);
    setModeActionChecked();
    connect(pacModeAction, &QAction::triggered, this, &StatusNotifier::onSetPacMode);
    connect(globalModeAction, &QAction::triggered, this, &StatusNotifier::onSetGlobalMode);
    changeModeMenu->addAction(pacModeAction);
    changeModeMenu->addAction(globalModeAction);

    systrayMenu.addAction(enableDisableAction);
    systrayMenu.addMenu(changeModeMenu);
    systrayMenu.addSeparator();
    systrayMenu.addAction(minimiseRestoreAction);
    systrayMenu.addAction(QIcon::fromTheme("application-exit", QIcon::fromTheme("exit")), tr("Quit"), qApp, SLOT(quit()));
    systray.setContextMenu(&systrayMenu);
    systray.show();
}

void StatusNotifier::activate()
{
    if (!window->isVisible() || window->isMinimized()) {
        window->showNormal();
        window->activateWindow();
        window->raise();
    } else {
        window->hide();
    }
}

void StatusNotifier::onChangeProxy()
{
    bool enable = window->configHelper->enable();
    int mode = window->configHelper->mode();

    if (enable) {
        enableDisableAction->setText("Enable Proxy");
        if (mode == 2) {
            window->httpServer->close();
            window->connection->disableProxy();
            qDebug() << "disable pac mode";
        } else {
            window->connection->disableProxy();
            qDebug() << "disable global mode";
        }
        window->configHelper->setEnable(false);
        changeModeMenu->setEnabled(false);
    } else {
        enableDisableAction->setText("Disable Proxy");
        if (mode == 2) {
            window->httpServer->listen();
            window->connection->setPacMode();
            qDebug() << "change to pac mode";

        } else {
            window->connection->setGlobalMode();
            qDebug() << "change to global mode";
        }
        window->configHelper->setEnable(true);
        changeModeMenu->setEnabled(true);
    }
}


void StatusNotifier::onSetPacMode()
{
    bool enable = window->configHelper->enable();
    int mode = window->configHelper->mode();
    bool checked = pacModeAction->isChecked();

    if (enable && mode == 1) {
        window->httpServer->listen();
        window->connection->setPacMode();
        qDebug() << "change to pac mode";
    }

    window->configHelper->setMode(2);
    setModeActionChecked();
}

void StatusNotifier::onSetGlobalMode()
{
    bool enable = window->configHelper->enable();
    int mode = window->configHelper->mode();

    if (enable && mode == 2) {
        window->httpServer->close();
        window->connection->setGlobalMode();
        qDebug() << "change to global mode";
    }

    window->configHelper->setMode(1);
    setModeActionChecked();
}

void StatusNotifier::setModeActionChecked()
{
    bool enable = window->configHelper->enable();
    int mode = window->configHelper->mode();

    if (mode == 2 && enable) {
        pacModeAction->setChecked(true);
        globalModeAction->setChecked(false);
    } else if (mode == 1 && enable) {
        globalModeAction->setChecked(true);
        pacModeAction->setChecked(false);
    }
}

void StatusNotifier::showNotification(const QString &msg)
{
    systray.showMessage("V2ray-Qt5", msg);
}

void StatusNotifier::onWindowVisibleChanged(bool visible)
{
    minimiseRestoreAction->setText(visible ? tr("Minimise") : tr("Restore"));
}
