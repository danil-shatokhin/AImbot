#ifndef LOGREADER_H
#define LOGREADER_H


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
    void ReportNewPlayer( QMap<QString, QString>& data );
    void ReportNewEntity( QMap<QString, QString>& data );

signals:
    void NewEntity(Entity &e);
    void EntityUpdate( int id, Field field, int new_value );
};

#endif // LOGREADER_H
