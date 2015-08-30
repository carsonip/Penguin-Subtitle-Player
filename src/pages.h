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
#include <QSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>


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
    QPlainTextEdit *dirEdit;
    //QLineEdit *adjustIntervalEdit;
    QSpinBox *adjustIntervalSpinBox;
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
    void openBgColorDialog();
    void openFontColorDialog();
    void openFontShadowColorDialog();
private:
    QColor openColorDialog(QColor initial);
    void paintColorButton(QPushButton *button, QColor color);
    QColor bgColor;
    QColor fontColor;
    QColor fontShadowColor;
    QSlider *bgAlphaSlider;
    QFontDialog *fontDialog;
    QPushButton *bgColorButton;
    QPushButton *fontColorButton;
    QPushButton *fontShadowColorButton;
    QCheckBox *rememberWindowPosAndSizeCbx;
    QCheckBox *fontShadowEnableCbx;
    QSpinBox *fontShadowBlurRadiusSpinBox;
    QSpinBox *fontShadowOffsetXSpinBox;
    QSpinBox *fontShadowOffsetYSpinBox;
};

#endif
