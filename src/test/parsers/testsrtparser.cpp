#include "testsrtparser.h"

#include <QString>

TestSrtParser::TestSrtParser() {}

void TestSrtParser::testParseFile() {
    QString fileContent = R"(1
00:00:00,050 --> 00:00:30,000
Foo

2
00:01:00,300 --> 00:02:00,900
Foo
Bar

3
00:03:45,150 --> 01:59:59,990
<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>

)";
    QTemporaryFile tmpFile;
    if (!tmpFile.open()) {
        QFAIL("Cannot open temp file");
    }
    QString filename = tmpFile.fileName();

    QTextStream outStream(&tmpFile);
    outStream << fileContent;
    tmpFile.close();

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QFAIL("Cannot read temp file");
    }

    std::vector<Engine::SubtitleItem> subtitles =
        SrtParser().parseFile(file, QString(""));
    QCOMPARE((int)subtitles.size(), 3);

    // normal case
    Engine::SubtitleItem item0(1, 50LL, 30000LL, "Foo");

    // multi-line case
    Engine::SubtitleItem item1(2, 60300LL, 120900LL, "Foo\nBar");

    // formatting inside text
    Engine::SubtitleItem item2(
        3, 225150LL, 7199990LL,
        "<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>");

    QCOMPARE(item0, subtitles[0]);
    QCOMPARE(item1, subtitles[1]);
    QCOMPARE(item2, subtitles[2]);
}
