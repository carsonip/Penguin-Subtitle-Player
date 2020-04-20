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
  w.show();
  if (argc > 1) {
    w.hide();
    QString path = a.arguments().at(1);
    w.load(path);
    w.show();
  }
  return a.exec();
}
