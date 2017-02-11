#include "testssaparser.h"

#include <QString>

TestSsaParser::TestSsaParser() {}

void TestSsaParser::testFormatText() {
    QString inputText = "{\\i1}Italics{\\i0}\\n{\\b1}Bold{\\b0}\\N{\\u1}"
                        "Underline{\\u0}{\\s1}Strikeout{\\s0}{\\ignoreme}";
    QString expected = "<i>Italics</i><br><b>Bold</b><br><u>Underline</"
                       "u><s>Strikeout</s>";
    QString actual = SsaParser::formatText(inputText);
    QCOMPARE(actual, expected);
}
