#include "logreader.h"
#include <QTextStream>

LogReader::LogReader(QString filename)
    : m_file(filename)
{
    QTextStream str(m_file, QIODevice::ReadOnly);
    QString data = str.readAll();
}
