#include "mainwindow.h"

MainWindow::MainWindow(ConfigHelper *confHelper, QWidget *parent) :
    configHelper(confHelper),
    QMainWindow(parent)
{
    ui.setupUi(this);

    bool isHideWindowOnStartup = configHelper->isHideWindowOnStartup();

    notifier = new StatusNotifier(this, isHideWindowOnStartup, this);
    profile = new SQProfile();
    controller = new Controller(profile, this);
    httpServer = new HttpServer(QHostAddress("127.0.0.1"), 1070, this);
    connection = new Connection(this, this);
    if (configHelper->mode() == 1) {
        connection->setGlobalMode();
    } else {
        connection->setPacMode();
        httpServer->listen();
    }
}


void MainWindow::hideEvent(QHideEvent *e)
{
    QMainWindow::hideEvent(e);
    notifier->onWindowVisibleChanged(false); 
}

void MainWindow::showEvent(QShowEvent *e)
{
    QMainWindow::showEvent(e);
    notifier->onWindowVisibleChanged(true);
    this->setFocus();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (e->spontaneous()) {
        e->ignore();
        hide();
    } else {
        QMainWindow::closeEvent(e);
    }
}
