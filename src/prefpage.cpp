#include "prefpage.h"

PrefPage::PrefPage(QWidget *parent, ConfigDialog *configDialog) : QWidget(parent)
{
    this->configDialog = configDialog;
}

PrefPage::~PrefPage()
{

}

