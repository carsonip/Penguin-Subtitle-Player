#include "srtparser.h"

#include "QDebug"
#include <QFile>
#include <QRegularExpression>
#include <QString>
#include <QTextCodec>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>

std::vector<Engine::SubtitleItem> SrtParser::parseFile(QFile &f,
                                                       QString encoding) {
  std::vector<Engine::SubtitleItem> subtitles;
  // Parsing the targeted .srt file.

  QTextStream in(&f);

  // Setting default encoding method to be UTF-8
  if (encoding.isEmpty())
    encoding = "UTF-8";

  if (QTextCodec::codecForName(encoding.toUtf8()))
    in.setCodec(encoding.toUtf8());
  else
    throw std::invalid_argument("Unknown Encoding");

  QString content = in.readAll();

  // Regex for capturing time information and subtitle content
  QRegularExpression patternStr(
      R"((\d+).*?\n(\d{2}):(\d{2}):(\d{2}),(\d{3}) --> (\d{2}):(\d{2}):(\d{2}),(\d{3}).*?\n([\s\S]*?)\n\n)");

  QRegularExpressionMatchIterator it = patternStr.globalMatch(content);
  // Fetching subtitle information one by one
  while (it.hasNext()) {
    QRegularExpressionMatch m = it.next();
    long section = m.captured(1).toLong();
    long long start = Engine::calculateTime(m.captured(2), m.captured(3),
                                            m.captured(4), m.captured(5));
    long long end = Engine::calculateTime(m.captured(6), m.captured(7),
                                          m.captured(8), m.captured(9));
    QString text = m.captured(10);
    // Validate current subtitle section against previous:
    Engine::SubtitleItem currentItem =
        Engine::SubtitleItem(section, start, end, this->formatText(text));
    Engine::SubtitleItem previousItem = Engine::SubtitleItem(0, 0, 0, "");
    // get previous (valid) subtitle section
    if (subtitles.size() > 0)
      previousItem = subtitles[subtitles.size() - 1];
    // add current subtitle section to either valid or invalid subtitles
    // variable
    if (Engine::validateItem(currentItem, previousItem))
      subtitles.push_back(currentItem);
    else {
      qDebug() << "Skipping invalid subtitle item, section number: "
               << currentItem.section;
    }
  }
  return subtitles;
}
