#ifndef TESTENGINE_H
#define TESTENGINE_H

#include <QtTest>

class TestEngine : public QObject {
  Q_OBJECT

public:
  TestEngine();

private:
  QString tmpFileName;
private slots:
  void initTestCase();
  void testGetFinishTime();
  void testCurrentSubtitleIndex();
  void testGetTimeWithSubtitleOffset();
  void cleanupTestCase();
};

#endif // TESTENGINE_H
