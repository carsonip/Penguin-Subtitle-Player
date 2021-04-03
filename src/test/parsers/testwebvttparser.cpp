#include "testwebvttparser.h"

#include <QString>

std::vector<Engine::SubtitleItem> getSubtitles(QString content) {
  QTemporaryFile tmpFile;
  if (!tmpFile.open()) {
    return std::vector<Engine::SubtitleItem>();
  }
  QString filename = tmpFile.fileName();

  QTextStream outStream(&tmpFile);
  outStream << content;
  tmpFile.close();

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return std::vector<Engine::SubtitleItem>();
  }

  std::vector<Engine::SubtitleItem> subtitles =
      WebVttParser().parseFile(file, QString(""));
  return subtitles;
}

void testString(QString content) {
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(content);
  QCOMPARE((int)subtitles.size(), 3);

  // normal case
  Engine::SubtitleItem item0(1, 50LL, 30000LL, "Foo");

  // multi-line case, with subtitle coordinates that should be ignored
  Engine::SubtitleItem item1(2, 60300LL, 120900LL, "Foo<br>Bar");

  // formatting inside text
  Engine::SubtitleItem item2(
      3, 225150LL, 7199990LL,
      "<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>");

  QCOMPARE(item0, subtitles[0]);
  QCOMPARE(item1, subtitles[1]);
  QCOMPARE(item2, subtitles[2]);
}

TestWebVttParser::TestWebVttParser() {}

void TestWebVttParser::testTimingFormat() {
  QString fileContent = R"(WEBVTT

00:00.050 --> 00:30.000
Foo

01:00.300 --> 00:02:00.900
Foo
Bar

03:45.150 --> 01:59:59.990
<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>

)";
  testString(fileContent);
}

void TestWebVttParser::testCueIdentifier() {
  QString fileContent = R"(WEBVTT

1
00:00:00.050 --> 00:00:30.000
Foo

2
00:01:00.300 --> 00:02:00.900
Foo
Bar

3
00:03:45.150 --> 01:59:59.990
<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>

)";
  testString(fileContent);
}

void TestWebVttParser::testLongHours() {
  QString fileContent = R"(WEBVTT

1
00:00:00.050 --> 1000:00:30.000
Foo

)";
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(fileContent);
  QCOMPARE((int)subtitles.size(), 1);
  QCOMPARE(Engine::SubtitleItem(1, 50LL, 3600030000LL, "Foo"), subtitles[0]);
}

void TestWebVttParser::testCueSetting() {
  QString fileContent = R"(WEBVTT

1
00:00:00.050 --> 00:00:30.000 line:63% position:72% align:start
Foo

2
00:01:00.300 --> 00:02:00.900 line:0 position:20% size:60% align:start
Foo
Bar

3
00:03:45.150 --> 01:59:59.990
<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>

)";
  testString(fileContent);
}

void TestWebVttParser::testStyleNote() {
  QString fileContent = R"(WEBVTT

STYLE
::cue {
  background-image: linear-gradient(to bottom, dimgray, lightgray);
  color: papayawhip;
}

NOTE comment blocks can be used between style blocks.

1
00:00:00.050 --> 00:00:30.000
Foo

2
00:01:00.300 --> 00:02:00.900
Foo
Bar

3
00:03:45.150 --> 01:59:59.990
<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>

)";
  testString(fileContent);
}
