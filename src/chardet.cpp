#include "charsetdetect.h"
#include <QString>
#include <QFile>
#include <fstream>

QString charsetDetect(QString path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly))
      throw std::invalid_argument("File IO Error");

  QByteArray bytes = file.readAll();
  const char *contents = bytes.constData();
  int size = bytes.size();

  csd_t csd = csd_open();
  csd_consider(csd, contents, size);

  return QString(csd_close(csd));
}
