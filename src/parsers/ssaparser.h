#ifndef SSAPARSER_H
#define SSAPARSER_H

#include "../parser.h"
#include <QRegularExpression>

class SsaParser : public Parser{

public:
    std::vector<SrtEngine::SubtitleItem> parseFile(QFile &f, QString encoding);
private:
    static long long timeFromStr(QString timeStr) {
        QRegularExpression patternStr("(\\d):(\\d{2}):(\\d{2}).(\\d{2})");
        QRegularExpressionMatch m = patternStr.match(timeStr);
        // the last match + "0" because time in SSA is expressed as h:mm:ss:xx (xx being hundredths of seconds)
        // need to multiply the xx by 10
        return SrtEngine::calculateTime(m.captured(1), m.captured(2), m.captured(3), m.captured(4) + "0");
    }
    static QString formatText(QString text) {
        text = text.replace(QRegExp("\\\\N"), "<br>");
        return text;
    }
};

#endif // SSAPARSER_H
