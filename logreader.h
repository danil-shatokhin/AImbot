#ifndef LOGREADER_H
#define LOGREADER_H
#include <entity.h>
#include <QFile>

class LogReader
{
    QFile m_log_file;
    int m_current_line;
public:
    LogReader(QString filename);
    void Update();
private:
    void Parse(QStringList data);
    inline QString Aquire(QString line, QString tag_name);
    void ReportNewGlobalEntity( QMap<QString, QString>& data );
    void ReportNewEntity( QMap<QString, QString>& data );

signals:
    void NewEntity(Entity &e);
    void EntityUpdate( int id, QString tag, QString new_value );
    void GlobalEntityUpdate( QString name, QString tag, QString value );
};

#endif // LOGREADER_H
