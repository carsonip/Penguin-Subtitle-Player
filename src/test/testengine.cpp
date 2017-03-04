#include "testengine.h"
#include "../engine.h"

TestEngine::TestEngine() {}

void TestEngine::initTestCase() {
    QString content = R"(1
00:00:00,050 --> 00:00:30,000
Foo

2
00:01:00,300 --> 00:02:00,900  X1:40 X2:600 Y1:20 Y2:50
Foo
Bar

3
00:03:45,150 --> 01:59:59,990
<i>Italics</i><br><b>Bold</b><br><u>Underline</u><s>Strikeout</s>

)";
    QFile tmpFile(QDir::tempPath() + "/XXXXXX.srt");
    if (!tmpFile.open(QIODevice::WriteOnly)) {
        QFAIL("Cannot open temp file");
    }
    tmpFileName = tmpFile.fileName();

    QTextStream outStream(&tmpFile);
    outStream << content;
    tmpFile.close();
}

void TestEngine::testCurrentSubtitleIndex() {
    Engine engine = Engine(tmpFileName, "");
    QCOMPARE(engine.currentSubtitleIndex(0LL, true), -1);      // before 0
    QCOMPARE(engine.currentSubtitleIndex(50LL, true), 0);      // start of 0
    QCOMPARE(engine.currentSubtitleIndex(1000LL, true), 0);    // inside 0
    QCOMPARE(engine.currentSubtitleIndex(30000LL, true), 0);   // end of 0
    QCOMPARE(engine.currentSubtitleIndex(60300LL, true), 1);   // start of 1
    QCOMPARE(engine.currentSubtitleIndex(70000LL, true), 1);   // inside 1
    QCOMPARE(engine.currentSubtitleIndex(120900LL, true), 1);  // end of 1
    QCOMPARE(engine.currentSubtitleIndex(225150LL, true), 2);  // start of 2
    QCOMPARE(engine.currentSubtitleIndex(325150LL, true), 2);  // inside 2
    QCOMPARE(engine.currentSubtitleIndex(7199990LL, true), 2); // end of 2
    QCOMPARE(engine.currentSubtitleIndex(9199990LL, true),
             2); // greater than end
}

void TestEngine::testGetFinishTime() {
    Engine engine = Engine(tmpFileName, "");
    QCOMPARE(engine.getFinishTime(), 7199990LL);
}

void TestEngine::cleanupTestCase() {
    QFile tmpFile(tmpFileName);
    tmpFile.remove();
}
