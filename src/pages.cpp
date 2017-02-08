#include "pages.h"
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
#include <QTextEdit>
#include <QFileDialog>
#include <QFontDialog>
#include <QPlainTextEdit>
#include <QPainter>
#include <QSpinBox>
#include "prefpage.h"
#include "QLineEdit"
#include "prefconstants.h"
#include <QCheckBox>
#include "configdialog.h"

void GeneralPage::load(){
    dirEdit->setPlainText(settings.value("gen/dir").toString());
    adjustIntervalSpinBox->setValue(settings.value("gen/adjust", QVariant::fromValue(PrefConstants::ADJUST_INTERVAL)).toInt());
}


void GeneralPage::save(){
    //qDebug() << "configsave";
    settings.setValue("gen/dir", dirEdit->toPlainText());
    settings.setValue("gen/adjust", adjustIntervalSpinBox->value());
}

void GeneralPage::openDirDialog(){
    QString path = QFileDialog::getExistingDirectory();
    if (!path.isNull()) dirEdit->setPlainText(path);
}

void GeneralPage::resetSettings(){
    settings.clear();
    this->configDialog->load();
}

GeneralPage::GeneralPage(QWidget *parent, ConfigDialog *configDialog)
    : PrefPage(parent, configDialog)
{
    QGroupBox *filesGroup = new QGroupBox(tr("Files"));

    QGroupBox *adjustGroup = new QGroupBox(tr("Adjustment"));

    QLabel *defaultDirLabel = new QLabel(tr("Default Directory:"));
    dirEdit = new QPlainTextEdit();
    QPushButton *dirBrowseButton = new QPushButton(tr("Browse"));
    connect(dirBrowseButton, SIGNAL(clicked()), this, SLOT(openDirDialog()));

    QLabel *adjustIntervalLabel = new QLabel(tr("Time Adjustment Interval (ms): "));
    adjustIntervalSpinBox = new QSpinBox();
    adjustIntervalSpinBox->setSingleStep(PrefConstants::ADJUST_INTERVAL_STEP);
    adjustIntervalSpinBox->setMaximum(PrefConstants::ADJUST_INTERVAL_MAX);

    QHBoxLayout *defaultDirLayout = new QHBoxLayout;
    defaultDirLayout->addWidget(defaultDirLabel);
    defaultDirLayout->addWidget(dirEdit);
    defaultDirLayout->addWidget(dirBrowseButton);

    QHBoxLayout *adjustIntervalLayout = new QHBoxLayout;
    adjustIntervalLayout->addWidget(adjustIntervalLabel);
    adjustIntervalLayout->addWidget(adjustIntervalSpinBox);
    adjustIntervalLayout->addStretch(1);

    QPushButton *resetButton = new QPushButton(tr("Reset All Preferences"));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetSettings()));

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(defaultDirLayout);
    filesGroup->setLayout(configLayout);

    QVBoxLayout *adjustLayout = new QVBoxLayout;
    adjustLayout->addLayout(adjustIntervalLayout);
    adjustGroup->setLayout(adjustLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(filesGroup);
    mainLayout->addStretch(1);
    mainLayout->addWidget(adjustGroup);
    mainLayout->addStretch(1);
    mainLayout->addWidget(resetButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    this->load();
}

QColor AppearancePage::openColorDialog(QColor initial){
    QColor color = QColorDialog::getColor(initial, 0, tr("Select Color"));
    if (color.isValid()){
        return color;
    }
    return initial;
}

void AppearancePage::openBgColorDialog(){
    bgColor = openColorDialog(bgColor);
    paintColorButton(bgColorButton, bgColor);
}

void AppearancePage::openFontColorDialog(){
    fontColor = openColorDialog(fontColor);
    paintColorButton(fontColorButton, fontColor);
}

void AppearancePage::openFontShadowColorDialog(){
    fontShadowColor = openColorDialog(fontShadowColor);
    paintColorButton(fontShadowColorButton, fontShadowColor);
}

void AppearancePage::load(){
    /* Window */
    bool isRememberWindowPosAndSize = settings.value("appearance/rememberWindowPosAndSize", QVariant::fromValue(PrefConstants::REMEMBER_WINDOW_POS_AND_SIZE)).toBool();
    rememberWindowPosAndSizeCbx->setChecked(isRememberWindowPosAndSize);
    bgColor = QColor::fromRgb(settings.value("appearance/bgColor", QVariant::fromValue(PrefConstants::BG_COLOR)).toUInt());
    paintColorButton(bgColorButton, bgColor);
    bgAlphaSlider->setValue(settings.value("appearance/bgAlpha", QVariant::fromValue(PrefConstants::BG_ALPHA)).toInt());

    /* Font */
    fontColor = QColor::fromRgb(settings.value("appearance/fontColor", QVariant::fromValue(PrefConstants::FONT_COLOR)).toUInt());
    paintColorButton(fontColorButton, fontColor);

    QFont initial;
    initial.fromString(settings.value("appearance/font").toString());
    fontDialog->setCurrentFont(initial);

    /* Font Shadow */
    bool isFontShadowEnable = settings.value("appearance/fontShadowEnable", QVariant::fromValue(PrefConstants::FONT_SHADOW_ENABLE)).toBool();
    fontShadowEnableCbx->setChecked(isFontShadowEnable);
    fontShadowColor = QColor::fromRgb(settings.value("appearance/fontShadowColor", QVariant::fromValue(PrefConstants::FONT_SHADOW_COLOR)).toUInt());
    paintColorButton(fontShadowColorButton, fontShadowColor);
    fontShadowBlurRadiusSpinBox->setValue(settings.value("appearance/fontShadowBlurRadius", QVariant::fromValue(PrefConstants::FONT_SHADOW_BLUR_RADIUS)).toInt());
    fontShadowOffsetXSpinBox->setValue(settings.value("appearance/fontShadowOffsetX", QVariant::fromValue(PrefConstants::FONT_SHADOW_OFFSET_X)).toInt());
    fontShadowOffsetYSpinBox->setValue(settings.value("appearance/fontShadowOffsetY", QVariant::fromValue(PrefConstants::FONT_SHADOW_OFFSET_Y)).toInt());
}


void AppearancePage::save(){
    /* Window */
    settings.setValue("appearance/rememberWindowPosAndSize", rememberWindowPosAndSizeCbx->isChecked());
    settings.setValue("appearance/bgColor", bgColor.rgb());
    settings.setValue("appearance/bgAlpha", bgAlphaSlider->value());

    /* Font */
    settings.setValue("appearance/fontColor", fontColor.rgb());
    settings.setValue("appearance/font", fontDialog->currentFont().toString());

    /* Font Shadow */
    settings.setValue("appearance/fontShadowEnable", fontShadowEnableCbx->isChecked());
    settings.setValue("appearance/fontShadowColor", fontShadowColor.rgb());
    settings.setValue("appearance/fontShadowBlurRadius", fontShadowBlurRadiusSpinBox->value());
    settings.setValue("appearance/fontShadowOffsetX", fontShadowOffsetXSpinBox->value());
    settings.setValue("appearance/fontShadowOffsetY", fontShadowOffsetYSpinBox->value());
}

AppearancePage::~AppearancePage(){

}

AppearancePage::AppearancePage(QWidget *parent, ConfigDialog *configDialog)
    : PrefPage(parent, configDialog)
{

    /* Window */
    QGroupBox *windowAppearanceGroup = new QGroupBox(tr("Window"));

    rememberWindowPosAndSizeCbx = new QCheckBox(tr("Remember last position and size"));

    QLabel *bgColorLabel = new QLabel(tr("Background Color: "));
    bgColorButton = new QPushButton();

    connect(bgColorButton, SIGNAL(clicked()), this, SLOT(openBgColorDialog()));

    QHBoxLayout *bgColorLayout = new QHBoxLayout;
    bgColorLayout->addWidget(bgColorLabel);
    bgColorLayout->addWidget(bgColorButton);
    bgColorLayout->addStretch(1);

    QLabel *bgAlphaLabel = new QLabel(tr("Opacity: "));
    bgAlphaSlider = new QSlider(Qt::Horizontal);
    bgAlphaSlider->setRange(PrefConstants::BG_ALPHA_MIN, 255);

    QHBoxLayout *bgAlphaLayout = new QHBoxLayout;
    bgAlphaLayout->addWidget(bgAlphaLabel);
    bgAlphaLayout->addWidget(bgAlphaSlider);

    QVBoxLayout *windowAppearanceLayout = new QVBoxLayout;
    windowAppearanceLayout->addWidget(rememberWindowPosAndSizeCbx);
    windowAppearanceLayout->addLayout(bgColorLayout);
    windowAppearanceLayout->addLayout(bgAlphaLayout);
    windowAppearanceGroup->setLayout(windowAppearanceLayout);


    /* Subtitle Font */
    QGroupBox *fontGroup = new QGroupBox(tr("Subtitle Font"));

    QLabel *fontColorLabel = new QLabel(tr("Font Color: "));
    fontColorButton = new QPushButton();
    connect(fontColorButton, SIGNAL(clicked()), this, SLOT(openFontColorDialog()));

    QHBoxLayout *fontColorLayout = new QHBoxLayout;
    fontColorLayout->addWidget(fontColorLabel);
    fontColorLayout->addWidget(fontColorButton);
    fontColorLayout->addStretch(1);

    fontDialog = new QFontDialog();
    fontDialog->setWindowFlags(Qt::Widget);
    fontDialog->setOptions(QFontDialog::NoButtons | QFontDialog::DontUseNativeDialog);

    QVBoxLayout *fontLayout = new QVBoxLayout;
    fontLayout->addLayout(fontColorLayout);
    fontLayout->addWidget(fontDialog);
    fontGroup->setLayout(fontLayout);


    /* Subtitle Font Drop Shadow */
    QGroupBox *fontShadowGroup = new QGroupBox(tr("Subtitle Font Shadow / Text Outline"));

    /* Enable */
    fontShadowEnableCbx = new QCheckBox(tr("Enable Shadow"));

    QHBoxLayout *fontShadowEnableLayout = new QHBoxLayout;
    fontShadowEnableLayout->addWidget(fontShadowEnableCbx);
    fontShadowEnableLayout->addStretch(1);

    /* Color */
    QLabel *fontShadowColorLabel = new QLabel(tr("Shadow Color: "));
    fontShadowColorButton = new QPushButton();
    connect(fontShadowColorButton, SIGNAL(clicked()), this, SLOT(openFontShadowColorDialog()));

    QHBoxLayout *fontShadowColorLayout = new QHBoxLayout;
    fontShadowColorLayout->addWidget(fontShadowColorLabel);
    fontShadowColorLayout->addWidget(fontShadowColorButton);
    fontShadowColorLayout->addStretch(1);

    /* Blur Radius */
    QLabel *fontShadowBlurRadiusLabel = new QLabel(tr("Blur Radius: "));
    fontShadowBlurRadiusSpinBox = new QSpinBox();
    fontShadowBlurRadiusSpinBox->setSingleStep(PrefConstants::FONT_SHADOW_BLUR_RADIUS_STEP);
    fontShadowBlurRadiusSpinBox->setMaximum(PrefConstants::FONT_SHADOW_BLUR_RADIUS_MAX);

    QHBoxLayout *fontShadowBlurRadiusLayout = new QHBoxLayout;
    fontShadowBlurRadiusLayout->addWidget(fontShadowBlurRadiusLabel);
    fontShadowBlurRadiusLayout->addWidget(fontShadowBlurRadiusSpinBox);
    fontShadowBlurRadiusLayout->addStretch(1);

    /* Offset */
    QLabel *fontShadowOffsetLabel = new QLabel(tr("Offset X, Y: "));
    fontShadowOffsetXSpinBox = new QSpinBox();
    fontShadowOffsetXSpinBox->setMinimum(-PrefConstants::FONT_SHADOW_OFFSET_LIMIT);
    fontShadowOffsetXSpinBox->setMaximum(PrefConstants::FONT_SHADOW_OFFSET_LIMIT);
    fontShadowOffsetYSpinBox = new QSpinBox();
    fontShadowOffsetYSpinBox->setMinimum(-PrefConstants::FONT_SHADOW_OFFSET_LIMIT);
    fontShadowOffsetYSpinBox->setMaximum(PrefConstants::FONT_SHADOW_OFFSET_LIMIT);

    QHBoxLayout *fontShadowOffsetLayout = new QHBoxLayout;
    fontShadowOffsetLayout->addWidget(fontShadowOffsetLabel);
    fontShadowOffsetLayout->addWidget(fontShadowOffsetXSpinBox);
    fontShadowOffsetLayout->addWidget(fontShadowOffsetYSpinBox);
    fontShadowOffsetLayout->addStretch(1);

    QVBoxLayout *fontShadowLayout = new QVBoxLayout;
    fontShadowLayout->addLayout(fontShadowEnableLayout);
    fontShadowLayout->addLayout(fontShadowColorLayout);
    fontShadowLayout->addLayout(fontShadowBlurRadiusLayout);
    fontShadowLayout->addLayout(fontShadowOffsetLayout);
    fontShadowGroup->setLayout(fontShadowLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(windowAppearanceGroup);
    mainLayout->addWidget(fontGroup);
    mainLayout->addWidget(fontShadowGroup);
    mainLayout->addSpacing(12);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    this->load();
}

void AppearancePage::paintColorButton(QPushButton *button, QColor color){
    QPixmap px(64, 64);
    QPainter pt(&px);
    pt.setBrush(color);
    pt.drawRect(0, 0, px.width()-1, px.height()-1);
    button->setIcon(color.isValid() ? px : QIcon());
}
