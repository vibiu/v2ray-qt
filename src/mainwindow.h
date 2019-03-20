#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "confighelper.h"
#include "ui_mainwindow.h"
#include "statusnotifier.h"
#include "controller.h"
#include "sqprofile.h"
#include "httpserver.h"
#include "connection.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ConfigHelper *confHelper, QWidget *parent = nullptr);

    ConfigHelper *configHelper;

    StatusNotifier *notifier;

    Controller *controller;

    SQProfile *profile;

    HttpServer *httpServer;

    Connection *connection;

private:
    Ui::MainWindowClass ui;

protected slots:
    void hideEvent(QHideEvent *e);
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);
};

#endif	// MAINWINDOW_H
