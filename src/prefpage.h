#ifndef PREFPAGE_H
#define PREFPAGE_H

#include "configdialog.h"
#include <QObject>
#include <QSettings>
#include <QWidget>

class PrefPage : public QWidget {
    Q_OBJECT
  public:
    explicit PrefPage(QWidget *parent = 0, ConfigDialog *configDialog = 0);
    ~PrefPage();
    virtual void save() = 0;
    virtual void load() = 0;
    QSettings settings;
    ConfigDialog *configDialog;
  signals:

  public slots:
};

#endif // PREFPAGE_H
