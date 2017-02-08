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
            long section = m.captured(1).toLong();
            long long start = calculateTime(m.captured(2), m.captured(3), m.captured(4), m.captured(5));
            long long end = calculateTime(m.captured(6), m.captured(7), m.captured(8), m.captured(9));
            QString text = m.captured(11);

            // Validate current subtitle section against previous:
            SubtitleItem currentItem = SubtitleItem(section,start,end,text);
            SubtitleItem previousItem = SubtitleItem(0,0,0,"");
            // get previous (valid) subtitle section
            if(subtitles.size() > 0)
                previousItem = subtitles[subtitles.size() - 1];
            // add current subtitle section to either valid or invalid subtitles variable
            if (validateItem(currentItem, previousItem))
                subtitles.push_back(currentItem);
            else{
                subtitles_invalid.push_back(currentItem);
                qDebug() << "Skipping invalid subtitle item, section number: " << currentItem.section;
            }
        }

    } catch(const exception& e) {

    }

    qDebug() << "Number of subtitle items imported: " << subtitles.size();
    if(subtitles_invalid.size() > 0)
        qDebug() << "Number of subtitle items skipped due to validation errors: " << subtitles_invalid.size();
}

bool SrtEngine::validateItem(SubtitleItem currentItem, SubtitleItem previousItem)
{
    // perform various validation checks on current subtitle item (section) compared to previous item

    bool valid = true; // assume valid unless fails one or more of following checks

    // check for current item start time before previous item start time
    if(currentItem.start < previousItem.start)
        valid = false;
    /* This checks fixes getFinishTime incorrectly reporting final item end time
     * as finish time when final item is out of time order (final item is invalid)
     */

    // check for current item end time before start time
    if(currentItem.end < currentItem.start)
        valid = false;

    return valid;
}

SrtEngine::~SrtEngine()
{

}

QString SrtEngine::currentSubtitle(long long time, bool sliderMoved)
{
    // Fetch the suitable subtitle content for current time

    if (subtitles.size() == 0)
        return "";

    if(!sliderMoved && time >= finishTime)
        return "";

    if(lastIndex != -1 && !sliderMoved){
        //  Linear search for next subtitle from last subtitle if slide bar is not manually set
        for (int i = lastIndex, len = subtitles.size(); i < len; i++) {
            SubtitleItem item = subtitles[i];
            if (time >= item.start && time <= item.end)
                return item.text;
        }
    }else{
        // Binary Search for initialization or if slide bar is manually set
        int lo = 0, hi = subtitles.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            SubtitleItem item = subtitles[mid];
            if (time >= item.start && time <= item.end){
                lo = mid;
                break;
            } else if (time > item.end) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        if (time >= subtitles[lo].start && time <= subtitles[lo].end){
            lastIndex = lo;
            return subtitles[lo].text;
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

