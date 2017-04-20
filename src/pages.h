#ifndef PAGES_H
#define PAGES_H

#include "prefpage.h"
#include <QCheckBox>
#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDebug>
#include <QFileDialog>
#include <QFontDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QVBoxLayout>

class GeneralPage : public PrefPage {
    Q_OBJECT
  public:
    GeneralPage(QWidget *parent = 0, ConfigDialog *configDialog = 0);
    void load();
    void save();
  public slots:
    void openDirDialog();
    void resetSettings();

  private:
    QPlainTextEdit *dirEdit;
    QCheckBox *useDetectedEncodingCbx;
    QSpinBox *adjustIntervalSpinBox;
};

class AppearancePage : public PrefPage {
    Q_OBJECT
  public:
    AppearancePage(QWidget *parent = 0, ConfigDialog *configDialog = 0);
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

class AboutPage : public PrefPage {
    Q_OBJECT
  public:
    AboutPage(QWidget *parent = 0, ConfigDialog *configDialog = 0);
    ~AboutPage();
    void load();
    void save();
};

#endif
