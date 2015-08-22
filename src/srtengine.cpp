#include "srtengine.h"
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

using namespace std;

SrtEngine::SrtEngine(QString path, QString encoding)
{
    // Constructing SrtEngine using the subtitle information of the path in specified encoding method
    if (path.isEmpty())
        return;

    try {
        // Parsing the targeted .srt file.

        QFile f(path);
        if (!f.open(QFile::ReadOnly | QFile::Text))
            throw std::invalid_argument("File IO Error");

        QTextStream in(&f);

        // Setting default encoding method to be UTF-8
        if(encoding.isEmpty())
            encoding = "UTF-8";

        if(QTextCodec::codecForName(encoding.toUtf8()))
            in.setCodec(encoding.toUtf8());
        else
            throw std::invalid_argument("Unknown Encoding");

        QString content = in.readAll();

        // Converting from CR-LF to LF line breaking
        content.remove(QChar('\r'));
        // Regex for capturing time information and subtitle content
        QRegularExpression patternStr("(\\d+)" + sp + nl
            + "(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3})" + sp
            + "-->" + sp + "(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3})" + sp
            + "(X1:\\d.*?)??" + nl + "([\\s\\S]*?)" + nl + nl);


        QRegularExpressionMatchIterator it = patternStr.globalMatch(content);
        // Fetching subtitle information one by one
        while (it.hasNext()) {
            QRegularExpressionMatch m = it.next();
            long long start = calculateTime(m.captured(2), m.captured(3), m.captured(4), m.captured(5));
            long long end = calculateTime(m.captured(6), m.captured(7), m.captured(8), m.captured(9));
            QString text = m.captured(11);
            subtitles.push_back(SubtitleItem(start,end,text));
        }

    } catch(const exception& e) {

    }
    qDebug() << "Number of subtitles: " << subtitles.size();
}

SrtEngine::~SrtEngine()
{

}

QString SrtEngine::currentSubtitle(long long time, bool sliderMoved)
{
    // Fetch the suitable subtitle content for current time

    if(!sliderMoved && time >= finishTime)
        return "";

    if(lastIndex != -1){
        //  Linear search for next subtitle from last subtitle if slide bar is not manually set
        for (int i = lastIndex, len = subtitles.size(); i < len; i++) {
            SubtitleItem item = subtitles[i];
            if (time >= item.start && time <= item.end)
                return item.text;
        }
    }else{
        // Binary Search for if slide bar is manually set

        int l = 0, m, h = subtitles.size() - 1;
        while (l <= h) {
            m = (l + h) / 2;
            SubtitleItem item = subtitles[m];

            if(time > item.end)
                l = m + 1;
            else
                h = m - 1;
        }
        for (int i = max(0, l - 3), len = min(l + 3, (int)subtitles.size()); i < len; i++)
            if (time >= subtitles[i].start && time <= subtitles[i].end) {
                lastIndex = i;
                return subtitles[i].text;
            }

        lastIndex = -1;

    }
    return "";
}

long long SrtEngine::getFinishTime()
{
    // Fetch the end time of last subtitle
    if (finishTime == 0LL && subtitles.size() > 0)
        finishTime = subtitles[subtitles.size() - 1].end;

    return finishTime;
}

