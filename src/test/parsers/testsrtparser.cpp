#include "testsrtparser.h"
#include "parsertests.h"
#include <QString>

TestSrtParser::TestSrtParser() {}

void TestSrtParser::testParseFileLf() {
  QString fileContent = R"(1
00:00:00,050 --> 00:00:30,000
Foo

2
00:01:00,300 --> 00:02:00,900  X1:40 X2:600 Y1:20 Y2:50
Foo
Bar

3
00:03:45,150 --> 01:59:59,990
<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>

)";
  SrtParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}

void TestSrtParser::testParseFileCrLf() {
  QString fileContent =
      "1\r\n"
      "00:00:00,050 --> 00:00:30,000\r\n"
      "Foo\r\n\r\n"
      "2\r\n"
      "00:01:00,300 --> 00:02:00,900  X1:40 X2:600 Y1:20 Y2:50\r\n"
      "Foo\r\n"
      "Bar\r\n\r\n"
      "3\r\n"
      "00:03:45,150 --> 01:59:59,990\r\n"
      "<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</"
      "s>\r\n\r\n";
  SrtParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}
