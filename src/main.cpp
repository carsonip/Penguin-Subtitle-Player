#include "QObject"
#include "QPushButton"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Penguin Subtitle Player");
    QCoreApplication::setOrganizationName("Carsons Lab");
    QCoreApplication::setOrganizationDomain("carsonslab.com");
    QCoreApplication::setApplicationName("Penguin Subtitle Player");
    MainWindow w;
    w.show();
    return a.exec();
}
