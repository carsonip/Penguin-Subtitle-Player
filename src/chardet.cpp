#include "uchardet/src/uchardet.h"
#include <QFile>
#include <QString>
#include <fstream>

QString charsetDetect(QString path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly))
    throw std::invalid_argument("File IO Error");

  QByteArray bytes = file.readAll();
  const char *contents = bytes.constData();
  int size = bytes.size();

  uchardet_t csd = uchardet_new();
  int rc = uchardet_handle_data(csd, contents, size);
  if (rc != 0) {
    uchardet_delete(csd);
    throw std::runtime_error("uchardet error " + std::to_string(rc));
  }
  uchardet_data_end(csd);
  QString encoding = QString(uchardet_get_charset(csd));
  uchardet_delete(csd);

  return encoding;
}
