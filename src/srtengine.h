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
        struct SubtitleItem;

    protected:
        // Specifying new line character and tabs in regex
        const QString nl = "\\n";
        const QString sp = "[ \\t]*";
    private:
        std::vector<SubtitleItem> subtitles;
        int lastIndex = -1;
        long long finishTime = 0LL;
    private:
        static long long calculateTime(QString h, QString m, QString s, QString ms){
            // Converting time information to milliseconds
            bool res;
            return h.toLongLong(&res, 10) * 60 * 60 * 1000 + m.toLongLong(&res, 10) * 60 * 1000 + s.toLongLong(&res, 10) * 1000 + ms.toLongLong(&res, 10);
        }
        static QString formatTime(long long x){
            if(x < 10) return "0" + QString::number(x, 10);
            else return QString::number(x, 10);
        }
    public:
        static QString millisToTimeString(long long ms){
            // Converting milliseconds to string in HH:MM:SS format

            int hours = ms / 60 / 60 / 1000;
            ms %= 60 * 60 * 1000;
            int minutes = ms / 60 / 1000;
            ms %= 60 * 1000;
            int seconds = ms / 1000;
            return formatTime(hours) + ":" + formatTime(minutes) + ":" + formatTime(seconds);

        }
    public:
        // Fetch the suitable subtitle content for current time
        QString currentSubtitle(long long time, bool sliderMoved);

        // Fetch the end time of last subtitle
        long long getFinishTime();

};

#endif // SRTENGINE_H
