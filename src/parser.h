#ifndef PARSER_H
#define PARSER_H

#include "engine.h"
#include "parserinterface.h"
#include "parsers/srtparser.h"
#include "parsers/ssaparser.h"
#include <QFile>
#include <QString>
#include <vector>

class Parser {
  public:
    Parser();
    ~Parser();
    std::vector<Engine::SubtitleItem> parseFile(QFile &f, QString encoding);
    QStringList getExtensions();
    QString getFileDialogExt();
    bool hasParser(QString ext);

  private:
    static std::vector<ParserInterface *> parsers;
};

#endif // PARSER_H
