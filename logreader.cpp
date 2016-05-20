#include "logreader.h"
#include <QTextStream>

LogReader::LogReader(QString filename)
    : m_file(filename), m_current_line(0)
{
    Update();
    QTextStream str(m_file, QIODevice::ReadOnly);
    QString data = str.readAll();
    m_current_pos(str.pos());
    Parse(data);
}

void LogReader::Update()
{
    QTextStream str(m_file, QIODevice::ReadOnly);
    QString buff = str.readAll();
    QStringList data = buff.split("\n");
    data.erase(data.begin(), data.begin()+m_current_line);

    int i=0;
    while (i!=data.size())
    {
        if (!data.at(i).startsWith("[Power]"))
            data.erase(i);
        ++i;
    }

    Parse(data);



}

void LogReader::Parse(QStringList data)
{
    int i = 0;
    while( i != data.size())
    {
        QString line = data.at(i).mid(37).trimmed();
        if (line.startsWith("Player"))
        {
            //new player
            QMap <QString, QString> map;
            int j = ++i;
            while (data.at(j).contains("tag"))
            {
                QString tag = Aquire( data.at(j), "tag=" );
                QString value = Aquire( data.at(j), "value=" );
                map[tag] = value;
            }
            ReportNewPlayer( map );
        }
        else if (line.startsWith("FULL_ENTITY"))
        {
            //new entity
            QMap <QString, QString> map;
            int j = ++i;
            while (data.at(j).contains("tag"))
            {
                QString tag = Aquire( data.at(j), "tag=" );
                QString value = Aquire( data.at(j), "value=" );
                map[tag] = value;
            }
            ReportNewEntity( map );
        }
        else if (line.startsWith("SHOW_ENTITY"))
        {
            //entity update
        }
        else if (line.startsWith("TAG_CHANGE"))
        {
            //parse block data
        }
        else
        {
            qDebug() << "UNKNWN LINE: " << line;
            i++;
        }
    }
}

QString LogReader::Aquire(QString line, QString tag_name)
{
    int begin = data.at(j).indexOf("tag=") + QString("tag").size();
    return data.at(j).mid(begin, data.at(j).indexOf(" "), begin);
}

void LogReader::ReportNewPlayer( QMap<QString, QString>& data )
{

}

void LogReader::ReportNewEntity( QMap<QString, QString>& data )
{

}
