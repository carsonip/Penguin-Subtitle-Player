#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdialog.h"
#include "prefconstants.h"
#include "srtengine.h"
#include "QMouseEvent"
#include "QObject"
#include "QDebug"
#include "QLayout"
#include "QSizeGrip"
#include "QTimer"
#include "string"
#include "QFileDialog"
#include "QString"
#include "QInputDialog"
#include "QTextCodec"
#include "QList"
#include "QByteArray"
#include "QIcon"
#include "QMenu"
#include "QAction"
#include "QDir"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QMimeData"
#include "QPainter"
#include "QGraphicsDropShadowEffect"
#include "chardet.h"

/*
 * Constructor and destructor
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this))
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/icon.png"));

    Qt::WindowFlags flags = this->windowFlags();

    this->setWindowFlags(flags | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); //
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    timer->setTimerType(Qt::PreciseTimer); // fixes subtitle delay
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    connect(ui->backwardButton, SIGNAL(clicked()), this, SLOT(fastBackward()));
    connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(fastForward()));

    connect(ui->toggleButton, SIGNAL(clicked()), this, SLOT(togglePlay()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    connect(ui->prefButton, SIGNAL(clicked()), this, SLOT(openSettingsWindow()));
    connect(ui->quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));


    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        trayIcon = new QSystemTrayIcon();
        trayIcon->setIcon(QIcon(":/icon.png"));

        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

        menu = new QMenu();

        QAction *settings = new QAction("Preferences", 0);
        connect(settings, SIGNAL(triggered()), this, SLOT(openSettingsWindow()));
        menu->addAction(settings);

        QAction *quit = new QAction("Quit", 0);
        connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
        menu->addAction(quit);

        trayIcon->setContextMenu(menu);

        trayIcon->show();
    }

    this->setAttribute(Qt::WA_Hover, true);

    ui->bottomWidgets->setAttribute(Qt::WA_NoMousePropagation); // fix window disappear problem

    bool isRememberWindowPosAndSize = settings.value("appearance/rememberWindowPosAndSize", QVariant::fromValue(PrefConstants::REMEMBER_WINDOW_POS_AND_SIZE)).toBool();
    if (isRememberWindowPosAndSize) this->loadPosAndSize();

    this->loadPref();
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    settings.setValue("appearance/windowX", this->x());
    settings.setValue("appearance/windowY", this->y());
    settings.setValue("appearance/windowWidth", this->width());
    settings.setValue("appearance/windowHeight", this->height());
    delete menu;
    delete trayIcon;
    delete engine;
    delete timer;
    delete ui;
}

/*
 * Public methods and slots
*/

void MainWindow::update()
{
    if (!engine)
        return;

    if (currentTime >= engine->getFinishTime()) {
        setPlay(false);
        return;
    }

    currentTime += INTERVAL;
    ui->subtitleLabel->setText(getSubtitle(false));
    ui->timeLabel->setText((SrtEngine::millisToTimeString(currentTime) + " / " + SrtEngine::millisToTimeString(engine->getFinishTime())));
    ui->horizontalSlider->setValue((int) (currentTime / SLIDER_RATIO));
}

void MainWindow::sliderMoved(int val)
{
    if (!engine)
        return;

    currentTime = val * SLIDER_RATIO;

    ui->subtitleLabel->setText(getSubtitle(true));
    ui->timeLabel->setText((SrtEngine::millisToTimeString(currentTime)+ " / " + SrtEngine::millisToTimeString(engine->getFinishTime())));
}

void MainWindow::togglePlay()
{
    if (!engine)
        return;

    if (currentTime >= engine->getFinishTime())
        setup();
    else setPlay(!isPlaying);
}

void MainWindow::fastForward()
{
    adjustTime(getAdjustInterval());
}

void MainWindow::fastBackward()
{
    adjustTime(-getAdjustInterval());
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        //qDebug() << "trigger";
    case QSystemTrayIcon::DoubleClick:
        //qDebug() << "double";
        break;
    case QSystemTrayIcon::MiddleClick:
        //qDebug() << "middle";
        break;
    case QSystemTrayIcon::Context:
        //qDebug() << "context";
        break;
    default:
        ;
    }
}

void MainWindow::openSettingsWindow()
{
    this->hide();
    ConfigDialog dialog;
    dialog.exec();
    this->show();
    this->loadPref();
}

void MainWindow::openFileDialog()
{
    this->hide();

    QString dir = settings.value("gen/dir").toString();
    if (!QDir(dir).exists()) dir = "";
    QString path = QFileDialog::getOpenFileName(0,
             tr("Open SRT File"), dir, tr("SRT Files (*.srt)"));

    if (!path.isNull()) {
        load(path);
    }

    this->show();
}

/*
 * Protected methods
*/

// fix shadowing problem in OS X
void MainWindow::paintEvent( QPaintEvent *event)
{
    QPainter p( this );
    p.setCompositionMode( QPainter::CompositionMode_Clear );
    p.fillRect( this->rect(), Qt::transparent );
}

/*
 * Private methods
*/

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    //qDebug() << "dragEnterEvent";
    if (e->mimeData()->hasUrls() && e->mimeData()->urls().size()==1)
        e->acceptProposedAction();

}

void MainWindow::dragMoveEvent()
{
    //qDebug() << "dragEvent";
}

void MainWindow::dropEvent(QDropEvent *e)
{
    this->hide();
    //qDebug() << "dropEvent";
    QString path = e->mimeData()->urls()[0].toLocalFile();
    //qDebug() << "Dropped file:" << path;
    if (!path.isNull() && path.toLower().right(4) == ".srt") {
        load(path);
    }
    this->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ClosedHandCursor);
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(Qt::OpenHandCursor);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void MainWindow::enterEvent(QEvent *event)
{
    //qDebug() << Q_FUNC_INFO << this->objectName();
    //QWidget::enterEvent(event);
    ui->verticalSpacer->changeSize(0,0);
    ui->bottomWidgets->show();
}

void MainWindow::leaveEvent(QEvent *event)
{
    //qDebug() << Q_FUNC_INFO << this->objectName();
    //QWidget::leaveEvent(event);
    ui->verticalSpacer->changeSize(0,ui->bottomWidgets->height() + ui->gridLayout->verticalSpacing());
    ui->bottomWidgets->hide();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (engine) ui->subtitleLabel->setText(getSubtitle(false));
}

void MainWindow::loadPosAndSize()
{
    int x = settings.value("appearance/windowX", QVariant::fromValue(PrefConstants::WINDOW_X)).toInt();
    int y = settings.value("appearance/windowY", QVariant::fromValue(PrefConstants::WINDOW_Y)).toInt();
    int w = settings.value("appearance/windowWidth", QVariant::fromValue(PrefConstants::WINDOW_WIDTH)).toInt();
    int h = settings.value("appearance/windowHeight", QVariant::fromValue(PrefConstants::WINDOW_HEIGHT)).toInt();
    this->setGeometry(x,y,w,h);
}

void MainWindow::loadPref()
{
    //qDebug() << settings.value("general/dir").toString();

    QColor bgColor = QColor::fromRgb(settings.value("appearance/bgColor", QVariant::fromValue(PrefConstants::BG_COLOR)).toUInt());
    int bgAlpha = settings.value("appearance/bgAlpha", QVariant::fromValue(PrefConstants::BG_ALPHA)).toInt();

    QString bgColorStr = QString("background-color:rgba(%1,%2,%3,%4)").arg(QString::number(bgColor.red()),QString::number(bgColor.green()),QString::number(bgColor.blue()),QString::number(bgAlpha));
    //qDebug() << bgColorStr;
    this->setStyleSheet(bgColorStr);

    QColor fontColor = QColor::fromRgb(settings.value("appearance/fontColor", QVariant::fromValue(PrefConstants::FONT_COLOR)).toUInt());
    ui->subtitleLabel->setStyleSheet(QString("background-color:transparent;"
                                     "color:rgba(%1,%2,%3)").arg(QString::number(fontColor.red()),QString::number(fontColor.green()),QString::number(fontColor.blue())));

    QFont f;
    f.fromString(settings.value("appearance/font").toString());
    ui->subtitleLabel->setFont(f);

    bool fontShadowEnable = settings.value("appearance/fontShadowEnable", QVariant::fromValue(PrefConstants::FONT_SHADOW_ENABLE)).toBool();
    if (fontShadowEnable) {
        QGraphicsDropShadowEffect * dse = new QGraphicsDropShadowEffect();
        dse->setBlurRadius(settings.value("appearance/fontShadowBlurRadius", QVariant::fromValue(PrefConstants::FONT_SHADOW_BLUR_RADIUS)).toInt());

        dse->setOffset(settings.value("appearance/fontShadowOffsetX", QVariant::fromValue(PrefConstants::FONT_SHADOW_OFFSET_X)).toReal(),
                       settings.value("appearance/fontShadowOffsetY", QVariant::fromValue(PrefConstants::FONT_SHADOW_OFFSET_Y)).toReal());

        QColor fontShadowColor = QColor::fromRgb(settings.value("appearance/fontShadowColor", QVariant::fromValue(PrefConstants::FONT_SHADOW_COLOR)).toUInt());
        dse->setColor(fontShadowColor);

        ui->subtitleLabel->setGraphicsEffect(dse);
    } else {
        ui->subtitleLabel->setGraphicsEffect(NULL);
    }
}

void MainWindow::load(QString path)
{
    QString chardet = charsetDetect(path);

    QString encoding = getEncoding(chardet);

    delete engine;
    engine = new SrtEngine(path, encoding);

    setup();
}

void MainWindow::setup()
{
    currentTime = 0;
    this->ui->horizontalSlider->setRange(0, (int) (engine->getFinishTime() / SLIDER_RATIO));
    this->ui->horizontalSlider->setEnabled(true);
    setPlay(true);
}


void MainWindow::setPlay(bool play)
{
    isPlaying = play;
    if (isPlaying)
        timer->start(INTERVAL);
    else
        timer->stop();
    ui->toggleButton->setIcon(QIcon(isPlaying?":/icons/ic_pause_48px.png":":/icons/ic_play_48px.png"));
}


QString MainWindow::getSubtitle(bool sliderMoved)
{
    QString subtitle = engine->currentSubtitle(currentTime, sliderMoved);
    // add ellipsis when subtitle is too long
    // QFontMetrics metrics(ui->subtitleLabel->font());
    // QString elidedText = metrics.elidedText(subtitle, Qt::ElideRight, ui->subtitleLabel->width());
    return subtitle;
}

QString MainWindow::getEncoding(QString preset)
{
    const QString AUTO_DETECT = " (Auto Detect)";

    bool ok;
    QStringList codecNames;

    QList<QByteArray> codecs = QTextCodec::availableCodecs();
    for (QList<QByteArray>::const_iterator it = codecs.constBegin(); it != codecs.constEnd(); it++) {
        codecNames.push_back(it->constData());
    }

    codecNames.sort();
    codecNames.removeDuplicates();

    int encodingIndex = 0;

    QString defaultEncoding = PrefConstants::ENCODING;
    int defaultEncodingIndex = codecNames.indexOf(defaultEncoding);
    if (defaultEncodingIndex >= 0) encodingIndex = defaultEncodingIndex;

    if (!preset.isNull() && !preset.isEmpty()){
        // find index of case insensitive search of preset encoding
        QStringList list = codecNames.filter(preset, Qt::CaseInsensitive);
        if (list.size() > 0) {
            encodingIndex = codecNames.indexOf(list[0]);
            codecNames[encodingIndex] += AUTO_DETECT;
        }
    }


    QString encoding = QInputDialog::getItem(0,  tr("Select Encoding"),tr("Select Encoding"), codecNames, encodingIndex, false, &ok);
    if (ok)
        return encoding.replace(AUTO_DETECT, "");

    return "";
}

void MainWindow::adjustTime(long long interval)
{
    if (!engine)
        return;
    currentTime = qMin(engine->getFinishTime(), qMax(0LL, currentTime + interval));
}

long long MainWindow::getAdjustInterval()
{
    //qDebug() << settings.value("gen/adjust").toInt();
    return settings.value("gen/adjust", QVariant::fromValue(PrefConstants::ADJUST_INTERVAL)).toInt();

}
