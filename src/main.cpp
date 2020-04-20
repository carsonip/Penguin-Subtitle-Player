#include "QObject"
#include "QPushButton"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setApplicationDisplayName("Penguin Subtitle Player");
  a.setOrganizationName("Carson Ip");
  a.setOrganizationDomain("carsonip.github.io");
  a.setApplicationName("Penguin Subtitle Player");
  a.setApplicationVersion(APP_VERSION);
  MainWindow w;
  if (argc > 1) {
    QString path = a.arguments().at(1);
    w.load(path);
  }
  w.show();
  a.setQuitOnLastWindowClosed(false);
  return a.exec();
}
