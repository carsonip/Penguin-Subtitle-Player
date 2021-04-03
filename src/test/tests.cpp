#include "tests.h"
#include "parsers/testsrtparser.h"
#include "parsers/testssaparser.h"
#include "parsers/testwebvttparser.h"
#include "testengine.h"

Tests::Tests() {}

void Tests::run() {
  TestSsaParser testSsaParser;
  QTest::qExec(&testSsaParser);

  TestSrtParser testSrtParser;
  QTest::qExec(&testSrtParser);

  TestWebVttParser testWebVttParser;
  QTest::qExec(&testWebVttParser);

  TestEngine testEngine;
  QTest::qExec(&testEngine);
}
