#include "charsetdetect.h"
#include <QString>
#include <fstream>

QString charsetDetect(QString path) {
  csd_t csd = csd_open();
  std::ifstream file(path.toUtf8().constData(),
                     std::ios::in | std::ios::binary | std::ios::ate);
  if (file.is_open()) {
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    char *contents = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(contents, size);
    file.close();
    csd_consider(csd, contents, size);
    delete[] contents;
  } else {
    throw std::invalid_argument("File IO Error");
  }
  return QString(csd_close(csd));
}
