#ifndef TESTWEBVTTPARSER_H
#define TESTWEBVTTPARSER_H

#include "../parsers/webvttparser.h"
#include <QtTest> //for unit testing

/**
 * @brief
 * 1. This class has to inherit from QObject:
 * 2. You need to include the QTest header
 * 3. Declare the test functions as private slots so the test framework finds
 * and executes it.
 */

class TestWebVttParser : public QObject {
  Q_OBJECT

public:
  TestWebVttParser();

private slots:
  void testTimingFormat();
  void testCueIdentifier();
  void testLongHours();
  void testCueSetting();
  void testStyleNote();
};

#endif // TESTWEBVTTPARSER_H
