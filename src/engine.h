#ifndef ENGINE_H
#define ENGINE_H

#include "QString"
#include "string"
#include "vector"

class Engine {

  public:
    Engine(QString path, QString encoding);
    ~Engine();

  public:
    struct SubtitleItem {
        /* Structure for storing each subtitle,
             * section stands for the source section (unique) identifer,
             * start, end stands for the starting and ending time in
         * milliseconds,
             * text stands for the content.
            */

        long section;
        long long start, end;
        QString text;
        SubtitleItem(long section, long long start, long long end,
                     QString text) {
            this->section = section;
            this->start = start;
            this->end = end;
            this->text = text;
        }
        bool operator==(const SubtitleItem &rhs) const {
            return this->section == rhs.section && this->start == rhs.start &&
                   this->end == rhs.end && this->text == rhs.text;
        }
    };

    static QString millisToTimeString(long long ms) {
        // Converting milliseconds to string in HH:MM:SS format

        int hours = ms / 60 / 60 / 1000;
        ms %= 60 * 60 * 1000;
        int minutes = ms / 60 / 1000;
        ms %= 60 * 1000;
        int seconds = ms / 1000;
        return formatTime(hours) + ":" + formatTime(minutes) + ":" +
               formatTime(seconds);
    }

    static long long calculateTime(QString h, QString m, QString s,
                                   QString ms) {
        // Converting time information to milliseconds
        return h.toLongLong() * 60 * 60 * 1000 + m.toLongLong() * 60 * 1000 +
               s.toLongLong() * 1000 + ms.toLongLong();
    }

    static QString formatTime(long long x) {
        if (x < 10)
            return "0" + QString::number(x, 10);
        else
            return QString::number(x, 10);
    }

    // Fetch the suitable subtitle content for current time
    QString currentSubtitle(long long time, bool sliderMoved);
    long long getTimeWithSubtitleOffset(long long time, int offset);
    int currentSubtitleIndex(long long time, bool sliderMoved);

    // Fetch the end time of last subtitle
    long long getFinishTime();

    static bool validateItem(SubtitleItem currentItem,
                             SubtitleItem previousItem) {
        // perform various validation checks on current subtitle item (section)
        // compared to previous item

        bool valid =
            true; // assume valid unless fails one or more of following checks

        // check for current item start time before previous item start time
        if (currentItem.start < previousItem.start)
            valid = false;
        /* This checks fixes getFinishTime incorrectly reporting final item end
         * time
         * as finish time when final item is out of time order (final item is
         * invalid)
         */

        // check for current item end time before start time
        if (currentItem.end < currentItem.start)
            valid = false;

        return valid;
    }

  private:
    std::vector<SubtitleItem> subtitles;
    int lastIndex = -1;
};

#endif // ENGINE_H
