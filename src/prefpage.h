#ifndef PREFPAGE_H
#define PREFPAGE_H

#include <QObject>
#include <QWidget>
#include <QSettings>

class PrefPage : public QWidget
{
    Q_OBJECT
public:
    explicit PrefPage(QWidget *parent = 0);
    ~PrefPage();
    virtual void save() = 0;
    virtual void load() = 0;
    QSettings settings;
signals:

public slots:
};

#endif // PREFPAGE_H
