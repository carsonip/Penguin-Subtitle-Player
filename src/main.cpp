#include "QObject"
#include "QPushButton"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Penguin Subtitle Player");
    QCoreApplication::setOrganizationName("Carson Ip");
    QCoreApplication::setOrganizationDomain("carsonip.github.io");
    QCoreApplication::setApplicationName("Penguin Subtitle Player");
    a.setApplicationVersion(APP_VERSION);
    MainWindow w;
    w.show();
    return a.exec();
}
