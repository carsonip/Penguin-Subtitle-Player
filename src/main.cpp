#include "QObject"
#include "QPushButton"
#include "QCommandLineParser"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setApplicationDisplayName("Penguin Subtitle Player");
  a.setOrganizationName("Carson Ip");
  a.setOrganizationDomain("carsonip.github.io");
  a.setApplicationName("Penguin Subtitle Player");
  a.setApplicationVersion(APP_VERSION);

  QCommandLineParser parser;
  parser.setApplicationDescription("Penguin Subtitle Player");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", QCoreApplication::translate("main", "Subtitle file to play, optionally."), "[file]");
  parser.process(a);
  const QStringList args = parser.positionalArguments();

  MainWindow w;
  if (args.length() > 0) {
    QString path = args.at(0);
    w.load(path);
  }
  w.show();
  a.setQuitOnLastWindowClosed(false);
  return a.exec();
}
