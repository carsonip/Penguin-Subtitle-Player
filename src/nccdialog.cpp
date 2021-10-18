#include "nccdialog.h"
#include "QDebug"
#include "QEvent"
#include "QHBoxLayout"
#include "QLabel"
#include "QPushButton"
#include "QVBoxLayout"
#include "QWidget"

NccDialog::NccDialog() {
  QPushButton *closeButton = new QPushButton(tr("Cancel"));

  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

  QHBoxLayout *buttonsLayout = new QHBoxLayout;
  buttonsLayout->addStretch(1);
  buttonsLayout->addWidget(closeButton);

  QLabel *label =
      new QLabel(tr("Next Click Counts feature activated.<br><b>Click outside "
                    "this dialog to start the timer.</b>"));
  label->setTextFormat(Qt::RichText);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(label);
  mainLayout->addStretch(1);
  mainLayout->addSpacing(12);
  mainLayout->addLayout(buttonsLayout);
  setLayout(mainLayout);

  setWindowTitle(tr("Next Click Counts"));
}

bool NccDialog::event(QEvent *event) {
  if (event->type() == QEvent::WindowDeactivate && !isClosed) {
    this->accept();
  } else if (event->type() == QEvent::Close) {
    isClosed = true;
  }

  return QWidget::event(event);
}
