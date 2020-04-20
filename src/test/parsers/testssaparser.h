#ifndef TESTSSAPARSER_H
#define TESTSSAPARSER_H

#include "../parsers/ssaparser.h"
#include <QtTest> //for unit testing

/**
 * @brief
 * 1. This class has to inherit from QObject:
 * 2. You need to include the QTest header
 * 3. Declare the test functions as private slots so the test framework finds
 * and executes it.
 */

class TestSsaParser : public QObject {
  Q_OBJECT

public:
  TestSsaParser();

private slots:
  void testFormatText();
  void testParseFile();
};

#endif // TESTSSAPARSER_H
