#ifndef PARSERINTERFACE_H
#define PARSERINTERFACE_H

#include <QString>
#include <vector>
#include <QFile>
#include "engine.h"

class ParserInterface {
   public:
      virtual std::vector<Engine::SubtitleItem> parseFile(QFile &f, QString encoding) = 0;
      virtual QStringList getExtensions() = 0;
};

#endif // PARSERINTERFACE_H
