#include "testssaparser.h"
#include "parsertests.h"
#include <QString>

TestSsaParser::TestSsaParser() {}

void TestSsaParser::testFormatText() {
  QString inputText =
      R"({\i1}Italics{\i0}\n{\b1}Bold{\b0}\N{\u1}Underline{\u0}{\s1}Strikeout{\s0}{\ignoreme})";
  QString expected = "<i>Italics</i><br><b>Bold</b><br><u>Underline</"
                     "u><s>Strikeout</s>";
  QString actual = SsaParser::formatText(inputText);
  QCOMPARE(actual, expected);
}

void TestSsaParser::testParseFile() {
  QString fileContent = R"([Script Info]
Title: <untitled>
Original Script: <unknown>
ScriptType: v4.00
PlayResY: 600
PlayDepth: 0
Timer: 100,0000

[v4+ Styles]
Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic,  Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding
Style: Default,Arial,20,&H00FFFFFF,&H00000000,&H00000000,&H00000000,0,0,0,0,100,100,0,0,1,2,0,2,15,15,15,0

[Events]
Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text
Dialogue: 0,0:00:00.05,0:00:30.00,Default,,0000,0000,0000,,Foo
Dialogue: 0,0:01:00.30,0:02:00.90,Default,,0000,0000,0000,,Foo\NBar
Dialogue: 0,0:03:45.15,1:59:59.99,Default,,0000,0000,0000,,{\i1}Italics{\i0}\n{\b1}Bold{\b0}\N{\u1}Underline{\u0}{\s1}Strikeout{\s0}{\ignoreme}
)";
  SsaParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}

void TestSsaParser::testParseFileComma() {
  QString fileContent = R"([Events]
Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text
Dialogue: 0,0:00:00.05,0:00:30.00,Default,,0000,0000,0000,,Foo,Bar
)";
  std::vector<Engine::SubtitleItem> expected{{1, 50LL, 30000LL, "Foo,Bar"}};

  SsaParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  QCOMPARE(subtitles, expected);
}

void TestSsaParser::testParseFileExtraWhitespace() {
  QString fileContent = R"( [Events]
 Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text
 Dialogue: 0,0:00:00.05,0:00:30.00,Default,,0000,0000,0000,,Foo
 Dialogue: 0,0:01:00.30,0:02:00.90,Default,,0000,0000,0000,,Foo\NBar
 Dialogue: 0,0:03:45.15,1:59:59.99,Default,,0000,0000,0000,,{\i1}Italics{\i0}\n{\b1}Bold{\b0}\N{\u1}Underline{\u0}{\s1}Strikeout{\s0}{\ignoreme}
)";
  SsaParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}

void TestSsaParser::testParseFileExtraNewline() {
  QString fileContent = R"([Events]
Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text
Dialogue: 0,0:00:00.05,0:00:30.00,Default,,0000,0000,0000,,Foo

Dialogue: 0,0:01:00.30,0:02:00.90,Default,,0000,0000,0000,,Foo\NBar
Dialogue: 0,0:03:45.15,1:59:59.99,Default,,0000,0000,0000,,{\i1}Italics{\i0}\n{\b1}Bold{\b0}\N{\u1}Underline{\u0}{\s1}Strikeout{\s0}{\ignoreme}
)";
  SsaParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}

void TestSsaParser::testParseFileTrimmedHeaders() {
  QString fileContent = R"([Events]
Format: Layer, Start , End , Style, Name, MarginL, MarginR, MarginV, Effect, Text
Dialogue: 0,0:00:00.05,0:00:30.00,Default,,0000,0000,0000,,Foo
Dialogue: 0,0:01:00.30,0:02:00.90,Default,,0000,0000,0000,,Foo\NBar
Dialogue: 0,0:03:45.15,1:59:59.99,Default,,0000,0000,0000,,{\i1}Italics{\i0}\n{\b1}Bold{\b0}\N{\u1}Underline{\u0}{\s1}Strikeout{\s0}{\ignoreme}
)";
  SsaParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}

void TestSsaParser::testParseFileMissingFormat() {
  QString fileContent = R"([Events]
Format: Layer, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text
Dialogue: 0,0:00:30.00,Default,,0000,0000,0000,,Foo
Dialogue: 0,0:02:00.90,Default,,0000,0000,0000,,Foo\NBar
Dialogue: 0,1:59:59.99,Default,,0000,0000,0000,,{\i1}Italics{\i0}\n{\b1}Bold{\b0}\N{\u1}Underline{\u0}{\s1}Strikeout{\s0}{\ignoreme}
)";
  bool isExceptionCaught = false;
  SsaParser p;
  try {
    std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  } catch (const std::exception &e) {
    QCOMPARE(e.what(), "Missing format for .ssa");
    isExceptionCaught = true;
  }
  QCOMPARE(isExceptionCaught, true);
}

void TestSsaParser::testParseFileSkipUselessLines() {
  QString fileContent = R"([Events]
foo
Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text
Dialogue: 0,0:00:00.05,0:00:30.00,Default,,0000,0000,0000,,Foo
bar
Dialogue: 0,0:01:00.30,0:02:00.90,Default,,0000,0000,0000,,Foo\NBar
Dialogue: 0,0:03:45.15,1:59:59.99,Default,,0000,0000,0000,,{\i1}Italics{\i0}\n{\b1}Bold{\b0}\N{\u1}Underline{\u0}{\s1}Strikeout{\s0}{\ignoreme}
)";
  SsaParser p;
  std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
  assertSubtitles(subtitles);
}

void TestSsaParser::testParseFileInvalidInput() {
  QStringList fileContents{R"([Events])", R"([Events]
)"};
  for (const QString &fileContent : fileContents) {
    SsaParser p;
    std::vector<Engine::SubtitleItem> subtitles = getSubtitles(p, fileContent);
    QCOMPARE((int)subtitles.size(), 0);
  }
}
