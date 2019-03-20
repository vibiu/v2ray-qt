#include "confighelper.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConfigHelper conf;

    MainWindow w(&conf);
    if (!conf.isHideWindowOnStartup()) {
        w.show();
    }
    return a.exec();
}
