#ifndef SSAPARSER_H
#define SSAPARSER_H

#include "../parserinterface.h"
#include <QRegularExpression>

class SsaParser : public ParserInterface {

  public:
    std::vector<Engine::SubtitleItem> parseFile(QFile &f, QString encoding);
    QStringList getExtensions() { return QStringList{".ssa", ".ass"}; }

    static long long timeFromStr(QString timeStr) {
        QRegularExpression patternStr("(\\d):(\\d{2}):(\\d{2}).(\\d{2})");
        QRegularExpressionMatch m = patternStr.match(timeStr);
        // the last match + "0" because time in SSA is expressed as h:mm:ss:xx
        // (xx being hundredths of seconds)
        // need to multiply the xx by 10
        return Engine::calculateTime(m.captured(1), m.captured(2),
                                     m.captured(3), m.captured(4) + "0");
    }
    static QString formatText(QString text) {
        // ASS Tags:
        // http://docs.aegisub.org/3.2/ASS_Tags/

        // soft line break and hard line break
        text = text.replace(QRegularExpression("\\\\n"), "<br>");
        text = text.replace(QRegularExpression("\\\\N"), "<br>");

        // ignore hard space
        text = text.replace(QRegularExpression("\\\\h"), "");

        // italics
        text = text.replace(QRegularExpression("\\{\\\\i1\\}"), "<i>");
        text = text.replace(QRegularExpression("\\{\\\\i0\\}"), "</i>");

        // bold
        text = text.replace(QRegularExpression("\\{\\\\b0\\}"), "</b>");
        text = text.replace(QRegularExpression("\\{\\\\b\\d+?\\}"), "<b>");

        // underline
        text = text.replace(QRegularExpression("\\{\\\\u1\\}"), "<u>");
        text = text.replace(QRegularExpression("\\{\\\\u0\\}"), "</u>");

        // strikeout
        text = text.replace(QRegularExpression("\\{\\\\s1\\}"), "<s>");
        text = text.replace(QRegularExpression("\\{\\\\s0\\}"), "</s>");

        // ignore and remove all other tags
        text = text.replace(QRegularExpression("\\{\\\\.*?\\}"), "");

        return text;
    }
};

#endif // SSAPARSER_H
