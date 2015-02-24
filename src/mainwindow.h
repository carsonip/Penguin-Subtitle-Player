#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "srtengine.h"
#include "QString"
#include <QSystemTrayIcon>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    void adjustTime(long long interval);
    long long getAdjustInterval();
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent();
    void dropEvent(QDropEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    void resizeEvent(QResizeEvent *event);

public slots:
    void fastForward();
    void fastBackward();
    void update();
    void openFileDialog();
    void sliderMoved(int);
    void togglePlay();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void openSettingsWindow();


private:
    long long int currentTime = 0LL;
    const long long int INTERVAL = 200LL;
    SrtEngine *engine = 0;
    QTimer *timer = 0;
    const long long int SLIDER_RATIO = 1000LL;
    void setup();
    void setPlay(bool);
    bool isPlaying = false;
    QString getEncoding();
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QSettings settings;
    void loadPref();
    QString getSubtitle(bool sliderMoved);
};

#endif // MAINWINDOW_H
