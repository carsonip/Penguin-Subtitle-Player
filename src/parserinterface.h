#ifndef PARSERINTERFACE_H
#define PARSERINTERFACE_H

#include "engine.h"
#include <QFile>
#include <QString>
#include <QStringList>
#include <vector>

class ParserInterface {
  public:
    virtual std::vector<Engine::SubtitleItem> parseFile(QFile &f,
                                                        QString encoding) = 0;
    virtual QStringList getExtensions() = 0;
};

#endif // PARSERINTERFACE_H
