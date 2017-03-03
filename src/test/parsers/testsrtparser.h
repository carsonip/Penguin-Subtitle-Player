#ifndef TESTSRTPARSER_H
#define TESTSRTPARSER_H

#include "../parsers/srtparser.h"
#include <QtTest> //for unit testing

/**
 * @brief
 * 1. This class has to inherit from QObject:
 * 2. You need to include the QTest header
 * 3. Declare the test functions as private slots so the test framework finds
 * and executes it.
 */

class TestSrtParser : public QObject {
    Q_OBJECT

  public:
    TestSrtParser();

  private:
    void testString(QString content);

  private slots:
    void testParseFileLf();
    void testParseFileCrLf();
};

#endif // TESTSRTPARSER_H
