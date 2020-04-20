#include "mainwindow.h"
#include "QAction"
#include "QByteArray"
#include "QDebug"
#include "QDesktopWidget"
#include "QDir"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QFileDialog"
#include "QGraphicsDropShadowEffect"
#include "QIcon"
#include "QInputDialog"
#include "QLayout"
#include "QLineEdit"
#include "QList"
#include "QMenu"
#include "QMessageBox"
#include "QMimeData"
#include "QMouseEvent"
#include "QObject"
#include "QPainter"
#include "QSizeGrip"
#include "QString"
#include "QStyle"
#include "QTextCodec"
#include "QTimer"
#include "chardet.h"
#include "cmath"
#include "configdialog.h"
#include "engine.h"
#include "parser.h"
#include "prefconstants.h"
#include "string"
#include "ui_mainwindow.h"

/*
 * Constructor and destructor
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), timer(new QTimer(this)) {
  ui->setupUi(this);

  this->setWindowIcon(QIcon(":/icon.png"));

  Qt::WindowFlags flags = this->windowFlags();

  this->setWindowFlags(flags | Qt::X11BypassWindowManagerHint |
                       Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); //
  this->setAttribute(Qt::WA_TranslucentBackground, true);

  timer->setTimerType(Qt::PreciseTimer); // fixes subtitle delay
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));

  connect(ui->backwardButton, SIGNAL(clicked()), this, SLOT(fastBackward()));
  connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(fastForward()));

  connect(ui->prevButton, SIGNAL(clicked()), this, SLOT(previous()));
  connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(next()));

  connect(ui->toggleButton, SIGNAL(clicked()), this, SLOT(togglePlay()));
  connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(openFileDialog()));
  connect(ui->prefButton, SIGNAL(clicked()), this, SLOT(openSettingsWindow()));
  connect(ui->quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
  connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this,
          SLOT(sliderMoved(int)));

  connect(ui->timeLabel, SIGNAL(clicked()), this, SLOT(openSkipToTimeDialog()));

  if (QSystemTrayIcon::isSystemTrayAvailable()) {
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icon.png"));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    menu = new QMenu();

    QAction *settings = new QAction("Preferences", menu);
    connect(settings, SIGNAL(triggered()), this, SLOT(openSettingsWindow()));
    menu->addAction(settings);

    QAction *quit = new QAction("Quit", menu);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    menu->addAction(quit);

    trayIcon->setContextMenu(menu);

    trayIcon->show();
  }

  this->setAttribute(Qt::WA_Hover, true);

  ui->bottomWidgets->setAttribute(
      Qt::WA_NoMousePropagation); // fix window disappear problem

  bool isRememberWindowPosAndSize =
      settings
          .value(
              "appearance/rememberWindowPosAndSize",
              QVariant::fromValue(PrefConstants::REMEMBER_WINDOW_POS_AND_SIZE))
          .toBool();
  if (isRememberWindowPosAndSize) {
    this->loadPosAndSize();
  } else {
    this->setGeometry(
        QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(),
                            qApp->desktop()->availableGeometry()));
  }

  bool resetSpeedFactorOnLaunch =
      settings
          .value(
              "gen/resetSpeedFactorOnLaunch",
              QVariant::fromValue(PrefConstants::RESET_SPEED_FACTOR_ON_LAUNCH))
          .toBool();
  if (resetSpeedFactorOnLaunch) {
    settings.setValue("gen/speedFactor", PrefConstants::SPEED_FACTOR);
  }

  this->loadPref();
  setAcceptDrops(true);
}

MainWindow::~MainWindow() {
  settings.setValue("appearance/windowX", this->x());
  settings.setValue("appearance/windowY", this->y());
  settings.setValue("appearance/windowWidth", this->width());
  settings.setValue("appearance/windowHeight", this->height());

  delete menu;
  delete engine;
  delete ui;
}

/*
 * Public methods and slots
 */

void MainWindow::update() {
  if (!engine)
    return;

  if (currentTime >= engine->getFinishTime()) {
    setPlay(false);
    return;
  }

  double add = speedFactor * INTERVAL;
  double intpart;
  double fracpart = modf(add, &intpart);

  // accumulate error
  intervalRemainder += fracpart;

  double remainderIntpart;
  intervalRemainder = modf(intervalRemainder, &remainderIntpart);

  // add integer part of error to currentTime
  currentTime += (int)intpart + (int)remainderIntpart;

  // to ensure it searches for all subtitles even after next / prev
  ui->subtitleLabel->setText(getSubtitle(skipped));
  skipped = false;

  ui->timeLabel->setText((Engine::millisToTimeString(currentTime) + " / " +
                          Engine::millisToTimeString(engine->getFinishTime())));
  ui->horizontalSlider->setValue((int)(currentTime / SLIDER_RATIO));
}

void MainWindow::sliderMoved(int val) {
  if (!engine)
    return;

  currentTime = val * SLIDER_RATIO;

  ui->subtitleLabel->setText(getSubtitle(true));
  ui->timeLabel->setText((Engine::millisToTimeString(currentTime) + " / " +
                          Engine::millisToTimeString(engine->getFinishTime())));
}

void MainWindow::togglePlay() {
  if (!engine)
    return;

  if (currentTime >= engine->getFinishTime())
    setup();
  else
    setPlay(!isPlaying);
}

void MainWindow::fastForward() {
  adjustTime(getAdjustInterval());
  update();
}

void MainWindow::fastBackward() {
  adjustTime(-getAdjustInterval());
  update();
}

void MainWindow::next() {
  if (!engine)
    return;
  long long time = engine->getTimeWithSubtitleOffset(currentTime, 1);
  currentTime = time;
  skipped = true;
  update();
}

void MainWindow::previous() {
  if (!engine)
    return;
  long long time = engine->getTimeWithSubtitleOffset(currentTime, -1);
  currentTime = time;
  skipped = true;
  update();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason) {
  switch (reason) {
  case QSystemTrayIcon::Trigger:
    break;
  case QSystemTrayIcon::DoubleClick:
    break;
  case QSystemTrayIcon::MiddleClick:
    break;
  case QSystemTrayIcon::Context:
    break;
  default:;
  }
}

void MainWindow::openSettingsWindow() {
  this->hide();
  ConfigDialog dialog;
  dialog.exec();
  this->show();
  this->loadPref();
}

void MainWindow::openFileDialog() {
  this->hide();

  QString dir = settings.value("gen/dir").toString();
  if (!QDir(dir).exists())
    dir = "";
  QString path = QFileDialog::getOpenFileName(
      0, tr("Open Subtitle File"), dir,
      tr("Subtitle Files") + " (" + Parser().getFileDialogExt() + ")");

  if (!path.isNull()) {
    load(path);
  }

  this->show();
}

void MainWindow::openSkipToTimeDialog() {
  if (!engine)
    return;

  this->hide();

  bool ok;
  QString timeStr = QInputDialog::getText(
      0, tr("Skip to Time"), tr("Skip to Time"), QLineEdit::Normal,
      Engine::millisToTimeString(currentTime), &ok);
  if (ok) {
    QRegularExpression timeRegex("^(\\d+):(\\d+):(\\d+)$");
    QRegularExpressionMatchIterator it = timeRegex.globalMatch(timeStr);
    if (it.hasNext()) {
      QRegularExpressionMatch match = it.next();
      QString h = match.captured(1), m = match.captured(2),
              s = match.captured(3);
      long long time = Engine::calculateTime(h, m, s, "0");
      currentTime = qMin(engine->getFinishTime(), qMax(0LL, time));
      update();
    }
  }
  this->show();
}

/*
 * Protected methods
 */

// fix shadowing problem in OS X
void MainWindow::paintEvent(QPaintEvent *event) {
  QPainter p(this);
  p.setCompositionMode(QPainter::CompositionMode_Clear);
  p.fillRect(this->rect(), Qt::transparent);
}

/*
 * Private methods
 */

void MainWindow::dragEnterEvent(QDragEnterEvent *e) {
  if (e->mimeData()->hasUrls() && e->mimeData()->urls().size() == 1)
    e->acceptProposedAction();
}

void MainWindow::dragMoveEvent() {}

void MainWindow::dropEvent(QDropEvent *e) {
  this->hide();
  QString path = e->mimeData()->urls()[0].toLocalFile();
  int index = path.lastIndexOf(".");
  QString ext = index == -1 ? "" : path.mid(index);

  if (!path.isNull() && index != -1 && Parser().hasParser(ext)) {
    load(path);
  }
  this->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  this->setCursor(Qt::ClosedHandCursor);
  m_nMouseClick_X_Coordinate = event->x();
  m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  this->setCursor(Qt::OpenHandCursor);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  move(event->globalX() - m_nMouseClick_X_Coordinate,
       event->globalY() - m_nMouseClick_Y_Coordinate);
}

void MainWindow::enterEvent(QEvent *event) {
  ui->topWidgets->show();
  ui->bottomWidgets->show();
}

void MainWindow::leaveEvent(QEvent *event) {
  ui->topWidgets->hide();
  ui->bottomWidgets->hide();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  if (engine)
    ui->subtitleLabel->setText(getSubtitle(false));
}

void MainWindow::loadPosAndSize() {
  int x = settings
              .value("appearance/windowX",
                     QVariant::fromValue(PrefConstants::WINDOW_X))
              .toInt();
  int y = settings
              .value("appearance/windowY",
                     QVariant::fromValue(PrefConstants::WINDOW_Y))
              .toInt();
  int w = settings
              .value("appearance/windowWidth",
                     QVariant::fromValue(PrefConstants::WINDOW_WIDTH))
              .toInt();
  int h = settings
              .value("appearance/windowHeight",
                     QVariant::fromValue(PrefConstants::WINDOW_HEIGHT))
              .toInt();
  this->setGeometry(x, y, w, h);
}

void MainWindow::loadPref() {
  speedFactor = settings
                    .value("gen/speedFactor",
                           QVariant::fromValue(PrefConstants::SPEED_FACTOR))
                    .toDouble();
  QColor bgColor =
      QColor::fromRgb(settings
                          .value("appearance/bgColor",
                                 QVariant::fromValue(PrefConstants::BG_COLOR))
                          .toUInt());
  int bgAlpha = settings
                    .value("appearance/bgAlpha",
                           QVariant::fromValue(PrefConstants::BG_ALPHA))
                    .toInt();

  QString bgColorStr =
      QString("background-color:rgba(%1,%2,%3,%4)")
          .arg(QString::number(bgColor.red()), QString::number(bgColor.green()),
               QString::number(bgColor.blue()), QString::number(bgAlpha));
  this->setStyleSheet(bgColorStr);

  QColor fontColor =
      QColor::fromRgb(settings
                          .value("appearance/fontColor",
                                 QVariant::fromValue(PrefConstants::FONT_COLOR))
                          .toUInt());
  ui->subtitleLabel->setStyleSheet(QString("background-color:transparent;"
                                           "color:rgba(%1,%2,%3)")
                                       .arg(QString::number(fontColor.red()),
                                            QString::number(fontColor.green()),
                                            QString::number(fontColor.blue())));

  QFont f;
  f.fromString(
      settings.value("appearance/font", PrefConstants::FONT).toString());
  ui->subtitleLabel->setFont(f);

  bool fontShadowEnable =
      settings
          .value("appearance/fontShadowEnable",
                 QVariant::fromValue(PrefConstants::FONT_SHADOW_ENABLE))
          .toBool();
  if (fontShadowEnable) {
    QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
    dse->setBlurRadius(
        settings
            .value("appearance/fontShadowBlurRadius",
                   QVariant::fromValue(PrefConstants::FONT_SHADOW_BLUR_RADIUS))
            .toInt());

    dse->setOffset(
        settings
            .value("appearance/fontShadowOffsetX",
                   QVariant::fromValue(PrefConstants::FONT_SHADOW_OFFSET_X))
            .toReal(),
        settings
            .value("appearance/fontShadowOffsetY",
                   QVariant::fromValue(PrefConstants::FONT_SHADOW_OFFSET_Y))
            .toReal());

    QColor fontShadowColor = QColor::fromRgb(
        settings
            .value("appearance/fontShadowColor",
                   QVariant::fromValue(PrefConstants::FONT_SHADOW_COLOR))
            .toUInt());
    dse->setColor(fontShadowColor);

    ui->subtitleLabel->setGraphicsEffect(dse);
  } else {
    ui->subtitleLabel->setGraphicsEffect(NULL);
  }
}

void MainWindow::load(QString path) {
  try {
    QString chardet = charsetDetect(path);
    qDebug() << "Detected Charset:" << chardet;
    if (chardet == "ASCII") {
      chardet = "UTF-8";
      qDebug() << "Chardet returns ASCII, use UTF-8 instead.";
    }

    // validates chardet result
    QString encoding = getEncoding(chardet);

    delete engine;
    engine = new Engine(path, encoding);
    setup();
  } catch (const std::exception &e) {
    QMessageBox::critical(NULL, "Error loading subtitle", e.what(),
                          QMessageBox::Ok, QMessageBox::Ok);
  }
}

void MainWindow::setup() {
  skipped = false;
  currentTime = 0;
  this->ui->subtitleLabel->setText(getSubtitle(false));
  this->ui->timeLabel->setText(
      (Engine::millisToTimeString(currentTime) + " / " +
       Engine::millisToTimeString(engine->getFinishTime())));
  this->ui->horizontalSlider->setRange(
      0, (int)(engine->getFinishTime() / SLIDER_RATIO));
  this->ui->horizontalSlider->setEnabled(true);
  setPlay(true);
}

void MainWindow::setPlay(bool play) {
  isPlaying = play;
  if (isPlaying)
    timer->start(INTERVAL);
  else
    timer->stop();
  ui->toggleButton->setIcon(QIcon(isPlaying ? ":/icons/ic_pause_48px.png"
                                            : ":/icons/ic_play_48px.png"));
}

QString MainWindow::getSubtitle(bool sliderMoved) {
  QString subtitle = engine->currentSubtitle(currentTime, sliderMoved);
  // add ellipsis when subtitle is too long
  // QFontMetrics metrics(ui->subtitleLabel->font());
  // QString elidedText = metrics.elidedText(subtitle, Qt::ElideRight,
  // ui->subtitleLabel->width());
  return subtitle;
}

QString MainWindow::getEncoding(QString preset) {
  QStringList codecNames;

  QList<QByteArray> codecs = QTextCodec::availableCodecs();
  for (QList<QByteArray>::const_iterator it = codecs.constBegin();
       it != codecs.constEnd(); it++) {
    codecNames.push_back(it->constData());
  }

  codecNames.sort();
  codecNames.removeDuplicates();

  int recommendIndex = -1;

  QString defaultEncoding = PrefConstants::ENCODING;
  QStringList defaultEncodingList =
      codecNames.filter(defaultEncoding, Qt::CaseInsensitive);
  if (defaultEncodingList.size() > 0)
    recommendIndex = codecNames.indexOf(defaultEncodingList[0]);

  if (!preset.isEmpty()) {
    // find index of case insensitive search of preset encoding
    QStringList list = codecNames.filter(preset, Qt::CaseInsensitive);
    if (list.size() > 0)
      recommendIndex = codecNames.indexOf(list[0]);
  }

  if (!settings
           .value("gen/useDetectedEncoding",
                  QVariant::fromValue(PrefConstants::USE_DETECTED_ENCODING))
           .toBool()) {
    QString chosenEncoding = promptForEncoding(codecNames, recommendIndex);
    if (!chosenEncoding.isEmpty())
      return chosenEncoding;
  }

  if (codecNames.size() == 0) {
    qDebug() << "No available codec";
    return "";
  }

  if (recommendIndex == -1) {
    qDebug() << "No recommended charset";
    recommendIndex = 0;
  }

  return codecNames[recommendIndex];
}

QString MainWindow::promptForEncoding(QStringList codecNames,
                                      int recommendIndex) {
  const QString RECOMMEND = " (Recommended)";
  if (recommendIndex != -1)
    codecNames[recommendIndex] += RECOMMEND;

  bool ok;
  QString encoding =
      QInputDialog::getItem(0, tr("Select Encoding"), tr("Select Encoding"),
                            codecNames, recommendIndex, false, &ok);
  if (ok)
    return encoding.replace(RECOMMEND, "");

  return "";
}

void MainWindow::adjustTime(long long interval) {
  if (!engine)
    return;
  currentTime =
      qMin(engine->getFinishTime(), qMax(0LL, currentTime + interval));
}

long long MainWindow::getAdjustInterval() {
  return settings
      .value("gen/adjust", QVariant::fromValue(PrefConstants::ADJUST_INTERVAL))
      .toInt();
}
