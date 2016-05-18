#ifndef LOGREADER_H
#define LOGREADER_H


class LogReader
{
    QFile m_log_file;
    uint64 current_pos;
public:
    LogReader(QString filename);
};

#endif // LOGREADER_H
