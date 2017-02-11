#include "configdialog.h"
#include "pages.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QSize>
#include <QStackedWidget>

void ConfigDialog::load() {
    QList<PrefPage *> list = pagesWidget->findChildren<PrefPage *>();
    for (PrefPage *page : list) {
        page->load();
    }
}

void ConfigDialog::save() {
    QList<PrefPage *> list = pagesWidget->findChildren<PrefPage *>();
    for (PrefPage *page : list) {
        page->save();
    }
    close();
}

ConfigDialog::ConfigDialog() {
    contentsWidget = new QListWidget;
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new GeneralPage(pagesWidget, this));
    pagesWidget->addWidget(new AppearancePage(pagesWidget, this));

    QPushButton *closeButton = new QPushButton(tr("Cancel"));
    QPushButton *okButton = new QPushButton(tr("OK"));

    createIcons();
    contentsWidget->setCurrentRow(0);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(save()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);
    buttonsLayout->addWidget(okButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Preferences"));
}

void ConfigDialog::createIcons() {
    const int HEIGHT = 50;
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setText(tr("General"));
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    configButton->setSizeHint(QSize(0, HEIGHT));

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setText(tr("Appearance"));
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    updateButton->setSizeHint(QSize(0, HEIGHT));

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changePage(QListWidgetItem *, QListWidgetItem *)));
}

void ConfigDialog::changePage(QListWidgetItem *current,
                              QListWidgetItem *previous) {
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
