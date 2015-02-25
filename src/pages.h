#ifndef PAGES_H
#define PAGES_H

#include "prefpage.h"
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QColorDialog>
#include <QDebug>
#include <QSettings>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QFontDialog>


class GeneralPage : public PrefPage
{
            Q_OBJECT
public:
    GeneralPage(QWidget *parent = 0);
    void load();
    void save();
public slots:
    void openDirDialog();
private:
    const int MAX_ADJUST_INTERVAL = 3600000;
    QPlainTextEdit *dirEdit;
    QLineEdit *adjustIntervalEdit;
};


class AppearancePage : public PrefPage
{
    Q_OBJECT
public:
    AppearancePage(QWidget *parent = 0);
    ~AppearancePage();
    void load();
    void save();
public slots:
    void openColorDialog();
    void openFontDialog();
private:
    QLabel *fontLabel;
    QColor bgColor;
    QSlider *bgAlphaSlider;
};

#endif
