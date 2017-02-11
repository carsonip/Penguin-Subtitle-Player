#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <vector>
#include <QFile>
#include "srtengine.h"
#include "parserinterface.h"
#include "parsers/srtparser.h"
#include "parsers/ssaparser.h"

class Parser {
   public:
      Parser();
      ~Parser();
      std::vector<SrtEngine::SubtitleItem> parseFile(QFile &f, QString encoding);
      QStringList getExtensions();
      QString getFileDialogExt();
      bool hasParser(QString ext);
   private:
      static std::vector<ParserInterface*> parsers;
};

#endif // PARSER_H
