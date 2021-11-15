#ifndef NCCDIALOG_H
#define NCCDIALOG_H

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class NccDialog : public QDialog {
  Q_OBJECT

public:
  NccDialog(bool toStart);
  bool event(QEvent *event);

private:
  bool isClosed = false;
};

#endif
