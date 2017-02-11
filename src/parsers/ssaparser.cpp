#include "ssaparser.h"

#include<iostream>
#include<algorithm>
#include<QString>
#include<vector>
#include<fstream>
#include<streambuf>
#include "QDebug"
#include<QFile>
#include<QTextCodec>
#include <QRegularExpression>

std::vector<SrtEngine::SubtitleItem> SsaParser::parseFile(QFile &f, QString encoding) {
    std::vector<SrtEngine::SubtitleItem> subtitles;

    QTextStream in(&f);

    // Setting default encoding method to be UTF-8
    if(encoding.isEmpty())
        encoding = "UTF-8";

    if(QTextCodec::codecForName(encoding.toUtf8()))
        in.setCodec(encoding.toUtf8());
    else
        throw std::invalid_argument("Unknown Encoding");

    while (!in.atEnd() && in.readLine() != "[Events]");

    QString formatLine = in.readLine();
    formatLine = formatLine.remove(0, 8); // remove "Format: "

    QStringList headers = formatLine.split(",");
    QStringList trimmedHeaders;
    for (QString h : headers){
        trimmedHeaders << h.trimmed();
    }
    headers = trimmedHeaders;

    int startIndex = headers.indexOf("Start");
    int endIndex = headers.indexOf("End");
    int textIndex = headers.indexOf("Text");

    QString line;
    while (!in.atEnd() && (line = in.readLine()) != ""){
        line = line.remove(0, 10); // remove "Dialogue: "
        QStringList columns = line.split(",");

        long long start = timeFromStr(columns[startIndex]);
        long long end = timeFromStr(columns[endIndex]);
        QString text = formatText(columns.mid(textIndex).join(","));
        subtitles.push_back(SrtEngine::SubtitleItem(0, start, end, text));
    }



    return subtitles;
}
