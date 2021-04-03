#include "parser.h"

std::vector<ParserInterface *> Parser::parsers;

Parser::Parser() {
  if (Parser::parsers.size() == 0) {
    Parser::parsers.push_back(new SrtParser);
    Parser::parsers.push_back(new SsaParser);
    Parser::parsers.push_back(new WebVttParser);
  }
}

Parser::~Parser() {
  // not deleting the parsers in static Parser::parsers
}

std::vector<Engine::SubtitleItem> Parser::parseFile(QFile &f,
                                                    QString encoding) {
  for (ParserInterface *p : Parser::parsers) {
    bool ok = false;
    for (QString ext : p->getExtensions()) {
      ok = ok || f.fileName().endsWith(ext, Qt::CaseInsensitive);
    }
    if (ok)
      return p->parseFile(f, encoding);
  }
  return std::vector<Engine::SubtitleItem>();
}

QStringList Parser::getExtensions() {
  QStringList list;
  for (ParserInterface *p : Parser::parsers) {
    list << p->getExtensions();
  }
  return list;
}

QString Parser::getFileDialogExt() {
  bool first = true;
  QString str = "";
  for (ParserInterface *p : Parser::parsers) {
    for (QString ext : p->getExtensions()) {
      str += QString(first ? "" : " ") + "*" + ext;
      first = false;
    }
  }
  return str;
}

bool Parser::hasParser(QString ext) {
  for (QString e : getExtensions()) {
    if (ext.compare(e, Qt::CaseInsensitive) == 0)
      return true;
  }
  return false;
}
