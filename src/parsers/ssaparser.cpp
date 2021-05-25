#include "ssaparser.h"

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

std::vector<Engine::SubtitleItem> SsaParser::parseFile(QFile &f,
                                                       QString encoding) {
  std::vector<Engine::SubtitleItem> subtitles;

  QTextStream in(&f);

  // Setting default encoding method to be UTF-8
  if (encoding.isEmpty())
    encoding = "UTF-8";

  if (QTextCodec::codecForName(encoding.toUtf8()))
    in.setCodec(encoding.toUtf8());
  else
    throw std::invalid_argument("Unknown Encoding");

  while (!in.atEnd() && in.readLine().trimmed() != "[Events]")
    ;

  QString line, formatLine;
  while (!in.atEnd()) {
    line = in.readLine().trimmed();
    if (line.startsWith("Format:")) {
      formatLine = line.remove(0, 7).trimmed();
      break;
    }
  }

  if (formatLine.isNull()) {
    return subtitles;
  }

  QStringList headers = formatLine.split(",");
  for (QString &h : headers) {
    h = h.trimmed();
  }

  int startIndex = headers.indexOf("Start");
  int endIndex = headers.indexOf("End");
  int textIndex = headers.indexOf("Text");
  if (startIndex == -1 || endIndex == -1 || textIndex == -1)
    throw std::runtime_error("Missing format for .ssa");

  long section = 0;
  while (!in.atEnd()) {
    line = in.readLine().trimmed();
    if (line.startsWith("Dialogue:")) {
      line = line.remove(0, 9).trimmed();

      QStringList columns = line.split(",");

      long long start = timeFromStr(columns[startIndex]);
      long long end = timeFromStr(columns[endIndex]);
      QString text = formatText(QStringList(columns.mid(textIndex)).join(","));
      subtitles.push_back(Engine::SubtitleItem(++section, start, end, text));
    }
  }

  return subtitles;
}
