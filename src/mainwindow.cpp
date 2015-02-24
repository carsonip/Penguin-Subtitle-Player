#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QObject"
#include "QDebug"
#include "QLayout"
#include "QSizeGrip"
#include "QTimer"
#include "string"
#include "QFileDialog"
#include "QString"
#include "srtengine.h"
#include "QInputDialog"
#include "QTextCodec"
#include "QList"
#include "QByteArray"
#include "QIcon"
#include "QMenu"
#include "QAction"
#include "configdialog.h"
#include "QDir"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QMimeData"

long long MainWindow::getAdjustInterval(){
    qDebug() << settings.value("gen/adjust").toInt();
    return settings.value("gen/adjust").toInt();

}

void MainWindow::adjustTime(long long interval){
    if(!engine) return;
    currentTime = qMin(engine->getFinishTime(), qMax(0LL, currentTime + interval));
}

void MainWindow::fastForward(){
    adjustTime(getAdjustInterval());
}

void MainWindow::fastBackward(){
    adjustTime(-getAdjustInterval());
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    qDebug() << "dragEnterEvent";
    if (e->mimeData()->hasUrls() && e->mimeData()->urls().size()==1) {
        e->acceptProposedAction();
    }
}
void MainWindow::dropEvent(QDropEvent *e)
{
    this->hide();
    qDebug() << "dropEvent";
    QString path = e->mimeData()->urls()[0].toLocalFile();
    qDebug() << "Dropped file:" << path;
    if (!path.isNull() && path.right(4) == ".srt"){
        QString encoding = getEncoding();

        delete engine;
        engine = new SrtEngine(path, encoding);
        qDebug() << "Correct File Type";
        setup();
    }
    this->show();
}
void MainWindow::dragMoveEvent()
{
    qDebug() << "dragEvent";
}

void MainWindow::openSettingsWindow(){
    this->hide();
    ConfigDialog dialog;
    dialog.exec();
    this->show();
    this->loadPref();
}

QString MainWindow::getSubtitle(bool sliderMoved){
    QString subtitle = engine->currentSubtitle(currentTime, sliderMoved);
    // add ellipsis when subtitle is too long
    // QFontMetrics metrics(ui->subtitleLabel->font());
    // QString elidedText = metrics.elidedText(subtitle, Qt::ElideRight, ui->subtitleLabel->width());
    return subtitle;
}

void MainWindow::sliderMoved(int val){
    if (!engine) return;

    currentTime = val * SLIDER_RATIO;

    ui->subtitleLabel->setText(getSubtitle(true));
    ui->timeLabel->setText((SrtEngine::millisToTimeString(currentTime)+ " / " + SrtEngine::millisToTimeString(engine->getFinishTime())));
}

void MainWindow::update(){
    if (!engine) return;
    if (currentTime >= engine->getFinishTime()){
        setPlay(false);
        return;
    }

    currentTime += INTERVAL;
    ui->subtitleLabel->setText(getSubtitle(false));
    ui->timeLabel->setText((SrtEngine::millisToTimeString(currentTime) + " / " + SrtEngine::millisToTimeString(engine->getFinishTime())));
    ui->horizontalSlider->setValue((int) (currentTime / SLIDER_RATIO));
}

void MainWindow::setPlay(bool play){
    isPlaying = play;
    if (isPlaying) timer->start(INTERVAL);
    else timer->stop();
    ui->toggleButton->setIcon(QIcon(isPlaying?":/icons/ic_pause_48px.png":":/icons/ic_play_48px.png"));
}

void MainWindow::togglePlay(){
    if (!engine) return;
    if (currentTime >= engine->getFinishTime()) setup();
    else setPlay(!isPlaying);
}

void MainWindow::setup(){
    currentTime = 0;
    this->ui->horizontalSlider->setRange(0, (int) (engine->getFinishTime() / SLIDER_RATIO));
    this->ui->horizontalSlider->setEnabled(true);
    setPlay(true);
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

void MainWindow::loadPref(){
    qDebug() << settings.value("general/dir").toString();

    QColor color = QColor::fromRgba(settings.value("appearance/bgcolor").toUInt());

    QString bgColor = QString("background-color:rgba(%1,%2,%3,%4)").arg(QString::number(color.red()),QString::number(color.green()),QString::number(color.blue()),QString::number(color.alpha()));
    qDebug() << bgColor;
    this->setStyleSheet(bgColor);

    QFont f;
    f.fromString(settings.value("appearance/font").toString());
    ui->subtitleLabel->setFont(f);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this))
{
    ui->setupUi(this);
    Qt::WindowFlags flags = this->windowFlags();
    //

    this->setWindowFlags(flags | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); //
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    connect(ui->backwardButton, SIGNAL(clicked()), this, SLOT(fastBackward()));
    connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(fastForward()));

    connect(ui->toggleButton, SIGNAL(clicked()), this, SLOT(togglePlay()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    connect(ui->prefButton, SIGNAL(clicked()), this, SLOT(openSettingsWindow()));
    connect(ui->quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));


    if (QSystemTrayIcon::isSystemTrayAvailable()){
        trayIcon = new QSystemTrayIcon();
        trayIcon->setIcon(QIcon(":/icon.png"));

        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

        menu = new QMenu();

        QAction *settings = new QAction("Settings", 0);
        connect(settings, SIGNAL(triggered()), this, SLOT(openSettingsWindow()));
        menu->addAction(settings);

        QAction *quit = new QAction("Quit", 0);
        connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
        menu->addAction(quit);

        trayIcon->setContextMenu(menu);

        trayIcon->show();
    }

    this->setAttribute(Qt::WA_Hover, true);

    this->loadPref();
    setAcceptDrops(true);
}

QString MainWindow::getEncoding(){
    bool ok;
    QStringList codecNames;

    QList<QByteArray> codecs = QTextCodec::availableCodecs();
    for (QList<QByteArray>::const_iterator it = codecs.constBegin(); it != codecs.constEnd(); it++){
        codecNames.push_back(it->constData());
    }
    //codecNames.sort();
    QString encoding = QInputDialog::getItem(0,  tr("Select Encoding"),tr("Select Encoding"), codecNames, 0, false, &ok);
    if (ok) return encoding;

    return "";
}

void MainWindow::openFileDialog(){
    this->hide();

    QString dir = settings.value("gen/dir").toString();
    if (!QDir(dir).exists()) dir = "";
    QString path = QFileDialog::getOpenFileName(0,
             tr("Open SRT File"), dir, tr("SRT Files (*.srt)"));

    if (!path.isNull()){
        QString encoding = getEncoding();

        delete engine;
        engine = new SrtEngine(path, encoding);

        setup();
    }


    this->show();

}

MainWindow::~MainWindow()
{
    delete menu;
    delete trayIcon;
    delete engine;
    delete timer;
    delete ui;

}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    this->setCursor(Qt::ClosedHandCursor);
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    this->setCursor(Qt::OpenHandCursor);
}

void MainWindow::enterEvent(QEvent * event)
{
    //qDebug() << Q_FUNC_INFO << this->objectName();
    //QWidget::enterEvent(event);
    ui->verticalSpacer->changeSize(0,0);
    ui->bottomWidgets->show();
}

void MainWindow::leaveEvent(QEvent * event)
{
    //qDebug() << Q_FUNC_INFO << this->objectName();
    //QWidget::leaveEvent(event);
    ui->verticalSpacer->changeSize(0,ui->bottomWidgets->height() + ui->gridLayout->verticalSpacing());
    ui->bottomWidgets->hide();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    if (engine) ui->subtitleLabel->setText(getSubtitle(false));
}
