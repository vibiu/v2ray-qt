#ifndef STATUSNOTIFIER_H
#define STATUSNOTIFIER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

class MainWindow;

class StatusNotifier: public QObject
{
    Q_OBJECT
public:
    StatusNotifier(MainWindow *w, bool StartHiden, QObject *parent = nullptr);

public slots:
    void activate();
    void showNotification(const QString &);
    void onChangeProxy();
    void onSetPacMode();
    void onSetGlobalMode();
    void onWindowVisibleChanged(bool visible);

private:
	void setModeActionChecked();
    QMenu systrayMenu;
    QAction *enableDisableAction;
    QMenu *changeModeMenu;
    QAction *pacModeAction;
    QAction *globalModeAction;
    QAction *minimiseRestoreAction;
    QSystemTrayIcon systray;
    MainWindow *window;
};

#endif  // STATUSNOTIFIER_H
