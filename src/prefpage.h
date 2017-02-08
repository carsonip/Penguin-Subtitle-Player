#ifndef PREFPAGE_H
#define PREFPAGE_H

#include <QObject>
#include <QWidget>
#include <QSettings>
#include "configdialog.h"

class PrefPage : public QWidget
{
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
