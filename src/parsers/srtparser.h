#ifndef SRTPARSER_H
#define SRTPARSER_H

#include "../parserinterface.h"

class SrtParser : public ParserInterface{

public:
    std::vector<Engine::SubtitleItem> parseFile(QFile &f, QString encoding);
    QStringList getExtensions() {
        return QStringList{".srt"};
    }

private:
    // Specifying new line character and tabs in regex
    const QString nl = "\\n";
    const QString sp = "[ \\t]*";
};

#endif // SRTPARSER_H
