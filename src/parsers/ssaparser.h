#ifndef SSAPARSER_H
#define SSAPARSER_H

#include "../parserinterface.h"
#include <QRegularExpression>

class SsaParser : public ParserInterface {

public:
  std::vector<Engine::SubtitleItem> parseFile(QFile &f, QString encoding);
  QStringList getExtensions() { return QStringList{".ssa", ".ass"}; }

  static long long timeFromStr(QString timeStr) {
    QRegularExpression patternStr(R"((\d):(\d{2}):(\d{2}).(\d{2}))");
    QRegularExpressionMatch m = patternStr.match(timeStr);
    // the last match + "0" because time in SSA is expressed as h:mm:ss:xx
    // (xx being hundredths of seconds)
    // need to multiply the xx by 10
    return Engine::calculateTime(m.captured(1), m.captured(2), m.captured(3),
                                 m.captured(4) + "0");
  }
  static QString formatText(QString text) {
    // ASS Tags:
    // http://docs.aegisub.org/3.2/ASS_Tags/

    // soft line break and hard line break
    text = text.replace(R"(\n)", "<br>");
    text = text.replace(R"(\N)", "<br>");

    // ignore hard space
    text = text.replace(R"(\h)", "");

    // italics
    text = text.replace(R"({\i1})", "<i>");
    text = text.replace(R"({\i0})", "</i>");

    // bold
    // pattern: \{\\b\d+?\}
    text = text.replace(R"({\b0})", "</b>");
    text = text.replace(
        QRegularExpression(QRegularExpression::escape(R"({\b)") + R"(\d+?)" +
                           QRegularExpression::escape(R"(})")),
        "<b>");

    // underline
    text = text.replace(R"({\u1})", "<u>");
    text = text.replace(R"({\u0})", "</u>");

    // strikeout
    text = text.replace(R"({\s1})", "<s>");
    text = text.replace(R"({\s0})", "</s>");

    // ignore and remove all other tags
    // pattern: \{\.*?\}
    text = text.replace(QRegularExpression(QRegularExpression::escape(R"({\)") +
                                           R"(.*?)" +
                                           QRegularExpression::escape(R"(})")),
                        "");

    return text;
  }
};

#endif // SSAPARSER_H
