#ifndef SRTENGINE_H
#define SRTENGINE_H

#include "string"
#include "vector"
#include "QString"

class SrtEngine
{

public:

    SrtEngine(QString path, QString encoding);
    ~SrtEngine();

public:

    struct SubtitleItem{
        /* Structure for storing each subtitle,
             * start, end stands for the starting and ending time in milliseconds,
             * text stands for the content.
            */

        long long start, end;
        QString text;
        SubtitleItem(long long start, long long end, QString text)
        {
            this->start = start;
            this->end = end;
            this->text = text;
        }
    };

    static QString millisToTimeString(long long ms)
    {
        // Converting milliseconds to string in HH:MM:SS format

        int hours = ms / 60 / 60 / 1000;
        ms %= 60 * 60 * 1000;
        int minutes = ms / 60 / 1000;
        ms %= 60 * 1000;
        int seconds = ms / 1000;
        return formatTime(hours) + ":" + formatTime(minutes) + ":" + formatTime(seconds);

    }

    static long long calculateTime(QString h, QString m, QString s, QString ms)
    {
        // Converting time information to milliseconds
        return h.toLongLong() * 60 * 60 * 1000 + m.toLongLong() * 60 * 1000 + s.toLongLong() * 1000 + ms.toLongLong();
    }

    static QString formatTime(long long x)
    {
        if(x < 10) return "0" + QString::number(x, 10);
        else return QString::number(x, 10);
    }

    // Fetch the suitable subtitle content for current time
    QString currentSubtitle(long long time, bool sliderMoved);

    // Fetch the end time of last subtitle
    long long getFinishTime();

private:

    // Specifying new line character and tabs in regex
    const QString nl = "\\n";
    const QString sp = "[ \\t]*";

    std::vector<SubtitleItem> subtitles;
    int lastIndex = -1;
    long long finishTime = 0LL;

};

#endif // SRTENGINE_H
