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

public slots:
    void update();
    void sliderMoved(int val);
    void togglePlay();
    void fastForward();
    void fastBackward();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void openSettingsWindow();
    void openFileDialog();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;

private:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent();
    void dropEvent(QDropEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);

    void loadPref();
    void setup();
    void setPlay(bool play);
    QString getSubtitle(bool sliderMoved);
    QString getEncoding();
    void adjustTime(long long interval);
    long long getAdjustInterval();


private:
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    long long int currentTime = 0LL;
    const long long int INTERVAL = 200LL;
    const long long int SLIDER_RATIO = 1000LL;
    SrtEngine *engine = 0;
    QTimer *timer = 0;
    bool isPlaying = false;
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QSettings settings;
};

#endif // MAINWINDOW_H
