#ifndef SRTPARSER_H
#define SRTPARSER_H

#include "../parserinterface.h"

class SrtParser : public ParserInterface {

  public:
    std::vector<Engine::SubtitleItem> parseFile(QFile &f, QString encoding);
    QStringList getExtensions() { return QStringList{".srt"}; }
};

#endif // SRTPARSER_H
