#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class ConfigDialog : public QDialog {
    Q_OBJECT

  public:
    void load();
    ConfigDialog();

  public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void save();

  private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
};

#endif
