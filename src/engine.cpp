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

    // Description of flag QIODevice::Text
    // When reading, the end-of-line terminators are translated to '\n'.
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::invalid_argument("File IO Error");

    try {
        subtitles = Parser().parseFile(f, encoding);
    } catch (const exception &e) {
    }

    qDebug() << "Number of subtitle items imported: " << subtitles.size();
}

Engine::~Engine() {}

QString Engine::currentSubtitle(long long time, bool sliderMoved) {
    int index = currentSubtitleIndex(time, sliderMoved);
    if (index < 0) {
        return "";
    }
    lastIndex = index;
    return subtitles[index].text;
}

long long Engine::getTimeWithSubtitleOffset(long long time, int offset) {
    int index = currentSubtitleIndex(time, true);
    int targetIndex;
    if (index >= 0) targetIndex = index + offset;
    else targetIndex = -(index+1) + (offset>0?offset-1:offset);

    if (targetIndex >= (int)subtitles.size())
        return this->getFinishTime();
    if (targetIndex < 0)
        return 0LL;

    return subtitles[targetIndex].start;
}

int Engine::currentSubtitleIndex(long long time, bool sliderMoved) {
    // Fetch the suitable subtitle content for current time
    // This function may return a negative value
    // -x-1 denotes the gap between x-1 and x
    // e.g. -1 is the gap between 0:00 and subtitles[0].start

    if (subtitles.size() == 0)
        return -1;

    if (time >= this->getFinishTime())
        return subtitles.size() - 1;

    if (!sliderMoved) {
        //  Linear search for next subtitle from last subtitle if slide bar is
        //  not manually set
        for (int i = max(0, lastIndex), len = subtitles.size(); i < len; i++) {
            SubtitleItem item = subtitles[i];
            if (time <= item.end) {
                if (time >= item.start) return i;
                else return -i-1;
            }
        }
    } else {
        // Binary Search for initialization or if slide bar is manually set
        int lo = 0, hi = subtitles.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            SubtitleItem item = subtitles[mid];
            if (time > item.end) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        if (time >= subtitles[lo].start && time <= subtitles[lo].end) {
            return lo;
        } else {
            return -lo-1;
        }
    }
    return -1;
}

long long Engine::getFinishTime() {
    // Fetch the end time of last subtitle
    if (subtitles.size() == 0)
        return 0LL;

    return subtitles[subtitles.size() - 1].end;
}
