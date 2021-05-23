#include "parsertests.h"
#include <QtTest>

std::vector<Engine::SubtitleItem> getSubtitles(ParserInterface &parser,
                                               QString content) {
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
      parser.parseFile(file, QString(""));
  return subtitles;
}

void assertSubtitles(std::vector<Engine::SubtitleItem> subtitles) {
  std::vector<Engine::SubtitleItem> expectedSubs;
  expectedSubs.push_back({1, 50LL, 30000LL, "Foo"});            // normal case
  expectedSubs.push_back({2, 60300LL, 120900LL, "Foo<br>Bar"}); // multi-line
  expectedSubs.push_back({3, 225150LL, 7199990LL,
                          "<i>Italics</i><br><b>Bold</b><br><u>Underline</"
                          "u><s>Strikeout</s>"}); // formatting inside text

  QCOMPARE(subtitles, expectedSubs);
}
