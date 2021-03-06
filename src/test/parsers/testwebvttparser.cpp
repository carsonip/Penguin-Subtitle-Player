#include "testwebvttparser.h"
#include "parsertests.h"
#include <QString>

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
  WebVttParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
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
  WebVttParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}

void TestWebVttParser::testLongHours() {
  QString fileContent = R"(WEBVTT

1
00:00:00.050 --> 1000:00:30.000
Foo

)";
  WebVttParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
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
  WebVttParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
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
  WebVttParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}
