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
#include "prefpage.h"
#include "QLineEdit"
#include "prefconstants.h"


void GeneralPage::load(){
   // qDebug() << settings.value("gen/dir").toString();
    dirEdit->setPlainText(settings.value("gen/dir").toString());
    adjustIntervalEdit->setText(settings.value("gen/adjust").toString());
}


void GeneralPage::save(){
    //qDebug() << "configsave";
    settings.setValue("gen/dir",dirEdit->toPlainText());
    settings.setValue("gen/adjust",adjustIntervalEdit->text());
}

void GeneralPage::openDirDialog(){
    QString path = QFileDialog::getExistingDirectory();
    if (!path.isNull()) dirEdit->setPlainText(path);
}

GeneralPage::GeneralPage(QWidget *parent)
    : PrefPage(parent)
{
    QGroupBox *filesGroup = new QGroupBox(tr("Files"));

    QGroupBox *adjustGroup = new QGroupBox(tr("Adjustment"));

    QLabel *defaultDirLabel = new QLabel(tr("Default Directory:"));
    dirEdit = new QPlainTextEdit();
    QPushButton *dirBrowseButton = new QPushButton(tr("Browse"));
    connect(dirBrowseButton, SIGNAL(clicked()), this, SLOT(openDirDialog()));

    QLabel *adjustIntervalLabel = new QLabel(tr("Time Adjustment Interval (ms): "));
    adjustIntervalEdit = new QLineEdit();
    adjustIntervalEdit->setMaxLength(9);
    adjustIntervalEdit->setValidator( new QIntValidator(0, MAX_ADJUST_INTERVAL, this) );

    QHBoxLayout *defaultDirLayout = new QHBoxLayout;
    defaultDirLayout->addWidget(defaultDirLabel);
    defaultDirLayout->addWidget(dirEdit);
    defaultDirLayout->addWidget(dirBrowseButton);

    QHBoxLayout *adjustIntervalLayout = new QHBoxLayout;
    adjustIntervalLayout->addWidget(adjustIntervalLabel);
    adjustIntervalLayout->addWidget(adjustIntervalEdit);

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
    setLayout(mainLayout);

    this->load();
}

void AppearancePage::openColorDialog(){
    QColor color = QColorDialog::getColor (bgColor, 0, tr("Select Color"));
    if (color.isValid()){
        bgColor = color;
        paintColorButton(bgColorButton, bgColor);
    }

}

void AppearancePage::load(){
    bgColor = QColor::fromRgb(settings.value("appearance/bgColor", QVariant::fromValue(PrefConstants::BG_COLOR)).toUInt());
    paintColorButton(bgColorButton, bgColor);
    bgAlphaSlider->setValue(settings.value("appearance/bgAlpha", QVariant::fromValue(PrefConstants::BG_ALPHA)).toInt());
    QFont initial;
    initial.fromString(settings.value("appearance/font").toString());
    fontDialog->setCurrentFont(initial);
}


void AppearancePage::save(){
    settings.setValue("appearance/font", fontDialog->currentFont().toString());
    settings.setValue("appearance/bgColor", bgColor.rgb());
    settings.setValue("appearance/bgAlpha", bgAlphaSlider->value());
}

AppearancePage::~AppearancePage(){

}

AppearancePage::AppearancePage(QWidget *parent)
    : PrefPage(parent)
{
    QGroupBox *windowAppearanceGroup = new QGroupBox(tr("Window"));

    QLabel *bgColorLabel = new QLabel(tr("Background Color: "));
    bgColorButton = new QPushButton();

    connect(bgColorButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));

    QHBoxLayout *bgColorLayout = new QHBoxLayout;
    bgColorLayout->addWidget(bgColorLabel);
    bgColorLayout->addWidget(bgColorButton);
    bgColorLayout->addStretch(1);

    QLabel *bgAlphaLabel = new QLabel(tr("Opacity: "));
    bgAlphaSlider = new QSlider(Qt::Horizontal);
    bgAlphaSlider->setRange(PrefConstants::BG_ALPHA_MIN, 255);

    QGroupBox *fontGroup = new QGroupBox(tr("Font"));

    QHBoxLayout *bgAlphaLayout = new QHBoxLayout;
    bgAlphaLayout->addWidget(bgAlphaLabel);
    bgAlphaLayout->addWidget(bgAlphaSlider);

    QVBoxLayout *windowAppearanceLayout = new QVBoxLayout;
    windowAppearanceLayout->addLayout(bgColorLayout);
    windowAppearanceLayout->addLayout(bgAlphaLayout);
    windowAppearanceGroup->setLayout(windowAppearanceLayout);

    fontDialog = new QFontDialog();
    fontDialog->setWindowFlags(Qt::Widget);
    fontDialog->setOptions(QFontDialog::NoButtons | QFontDialog::DontUseNativeDialog);

    QVBoxLayout *fontLayout = new QVBoxLayout;
    fontLayout->addWidget(fontDialog);
    fontGroup->setLayout(fontLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(windowAppearanceGroup);
    mainLayout->addWidget(fontGroup);
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
