#ifndef WEBVTTPARSER_H
#define WEBVTTPARSER_H

#include "../parserinterface.h"

class WebVttParser : public ParserInterface {

public:
  std::vector<Engine::SubtitleItem> parseFile(QFile &f, QString encoding);
  QStringList getExtensions() { return QStringList{".vtt"}; }
  static QString formatText(QString text) {
    text = text.replace("\n", "<br>");
    return text;
  }
};

#endif // SRTPARSER_H
