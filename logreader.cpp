#include "logreader.h"
#include <QTextStream>
#include <QStringList>

LogReader::LogReader(QString filename)
    : m_log_file(filename), m_current_line(0)
{
    Update();
    QString data = m_log_file.readAll();
    Parse(data.split("\n"));
}

void LogReader::Update()
{
    QString buff = m_log_file.readAll();
    QStringList data = buff.split("\n");
    data.erase(data.begin(), data.begin()+m_current_line);

    auto it=data.begin();
    while (it!=data.end())
    {
        if (!(*it).startsWith("[Power]"))
            data.erase(it);
        ++it;
    }

    Parse(data);
}

void LogReader::Parse(QStringList data)
{
    int i = 0;
    while( i != data.size())
    {
        QString line = data.at(i).mid(37).trimmed();
        if (line.startsWith("GameEntity"))
        {
            QMap <QString, QString> map;

            map["type"] = "GAME_ENTITY";
            map["id"] = Aquire(line, "EntityID=");

            int j = ++i;
            while (data.at(j).startsWith("tag="))
            {
                QString tag = Aquire( data.at(j), "tag=" );
                QString value = Aquire( data.at(j), "value=" );
                map[tag] = value;
                j = ++i;
            }
            ReportNewEntity( map );
        }
        if (line.startsWith("Player"))
        {
            //new player or game
            QMap <QString, QString> map;
            map["type"] = "PLAYER";
            map["id"] = Aquire(line, "EntityID=");

            if ()
            QString card_id = Aquire(line, "CardID=");

            map["card_id"] = card_id;

            int j = ++i;
            while (data.at(j).startsWith("tag="))
            {
                QString tag = Aquire( data.at(j), "tag=" );
                QString value = Aquire( data.at(j), "value=" );
                map[tag] = value;
                j = ++i;
            }
            ReportNewEntity( map );
        }
        else if (line.startsWith("FULL_ENTITY"))
        {
            //new entity
            QMap <QString, QString> map;
            map["type"] = "CARD";
            map["id"] = Aquire(line, "ID=");
            map["card_id"] = Aquire(line, "CardID=");

            int j = ++i;
            while (data.at(j).startsWith("tag"))
            {
                QString tag = Aquire( data.at(j), "tag=" );
                QString value = Aquire( data.at(j), "value=" );
                map[tag] = value;
                j = ++i;
            }
            ReportNewEntity( map );
        }
        else if (line.startsWith("SHOW_ENTITY"))
        {
            //entity update
            QString entity_id = Aquire(line, "id=");

            QString card_id = Aquire(line, "CardID=");
            emit EntityUpdate(entity_id, "cardid", card_id);

            int j = ++i;
            while (data.at(j).startsWith("tag="))
            {
                QString tag_name = Aquire(data.at(j), "tag=");
                QString value = Aquire(data.at(j), "value=");
                emit EntityUpdate( entity_id, tag_name, value );
                j = ++i;
            }
        }
        else if (line.startsWith("TAG_CHANGE"))
        {
            //parse block data
            QString tag_name = Aquire(line, "tag=");
            QString value = Aquire( line, "value=" );
            if (line.contains("id="))
            {
                QString id = Aquire(line, "id=");
                emit EntityUpdate( id.toInt(), tag_name, value );
            }
            else
            {
                QString name = Aquire(line, "Entity=");
                emit GlobalEntityUpdate( name, tag_name, value );
            }
            i++;
        }
        else
        {
            qDebug() << "UNKNWN LINE: " << line;
            i++;
        }
    }
    m_current_line = i;
}

QString LogReader::Aquire(QString line, QString tag_name)
{
    int begin = data.at(j).indexOf("tag=") + QString("tag").size();
    return data.at(j).mid(begin, data.at(j).indexOf(" "), begin);
}

void LogReader::ReportNewEntity( QMap<QString, QString>& data )
{
    Entity e;
    foreach( QPair<QString, QString> p, data )
    {
        e.AddTag(p.first, p.second);
    }

    emit NewEntity(e);
}
