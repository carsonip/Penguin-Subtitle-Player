#include "tests.h"
#include "parsers/testssaparser.h"

Tests::Tests() {}

void Tests::run() {
    TestSsaParser testSsaParser;
    QTest::qExec(&testSsaParser);
}
