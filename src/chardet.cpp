#include "charsetdetect.h"
#include <QString>
#include <fstream>

using namespace std;

QString charsetDetect(QString path) {
  csd_t csd = csd_open();
  ifstream file(path.toUtf8().constData(), ios::in | ios::binary | ios::ate);
  if (file.is_open()) {
    file.seekg(0, ios::end);
    streampos size = file.tellg();
    char *contents = new char[size];
    file.seekg(0, ios::beg);
    file.read(contents, size);
    file.close();
    csd_consider(csd, contents, size);
    delete[] contents;
  } else {
    throw std::invalid_argument("File IO Error");
  }
  return QString(csd_close(csd));
}
