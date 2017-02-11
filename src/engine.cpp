#include "engine.h"
#include "QDebug"
#include <QString>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>

#include <QFile>
#include <QRegularExpression>
#include <QTextCodec>

#include "parser.h"

using namespace std;

Engine::Engine(QString path, QString encoding) {
    // Constructing Engine using the subtitle information of the path in
    // specified encoding method
    if (path.isEmpty())
        return;

    QFile f(path);
    if (!f.open(QFile::ReadOnly | QFile::Text))
        throw std::invalid_argument("File IO Error");

    try {
        subtitles = Parser().parseFile(f, encoding);
    } catch (const exception &e) {
    }

    qDebug() << "Number of subtitle items imported: " << subtitles.size();
    if (subtitles_invalid.size() > 0)
        qDebug()
            << "Number of subtitle items skipped due to validation errors: "
            << subtitles_invalid.size();
}

Engine::~Engine() {}

QString Engine::currentSubtitle(long long time, bool sliderMoved) {
    // Fetch the suitable subtitle content for current time

    if (subtitles.size() == 0)
        return "";

    if (!sliderMoved && time >= this->getFinishTime())
        return "";

    if (lastIndex != -1 && !sliderMoved) {
        //  Linear search for next subtitle from last subtitle if slide bar is
        //  not manually set
        for (int i = lastIndex, len = subtitles.size(); i < len; i++) {
            SubtitleItem item = subtitles[i];
            if (time >= item.start && time <= item.end)
                return item.text;
        }
    } else {
        // Binary Search for initialization or if slide bar is manually set
        int lo = 0, hi = subtitles.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            SubtitleItem item = subtitles[mid];
            if (time >= item.start && time <= item.end) {
                lo = mid;
                break;
            } else if (time > item.end) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        if (time >= subtitles[lo].start && time <= subtitles[lo].end) {
            lastIndex = lo;
            return subtitles[lo].text;
        }
        lastIndex = -1;
    }
    return "";
}

long long Engine::getFinishTime() {
    // Fetch the end time of last subtitle
    if (subtitles.size() == 0)
        return 0LL;

    return subtitles[subtitles.size() - 1].end;
}
