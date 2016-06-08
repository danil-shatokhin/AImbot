#include "logreader.h"
#include <QTextStream>
#include <QStringList>

LogReader::LogReader(QString filename)
    : m_log_file(filename), m_current_line(0)
{
}

void LogReader::Update()
{
    QString buff;
    if (m_log_file.open(QIODevice::ReadOnly))
    {
        buff = m_log_file.readAll();
        m_log_file.close();
    }

    QStringList data = buff.split("\n");
    QStringList power_data;
    for (int i=0; i<data.size(); i++)
    {
        if (data.at(i).startsWith("[Power]"))
            power_data.append(data.at(i));
    }

    /*int i = 0;
    while(i != m_current_line || data.size())
    {
        data.erase(data.begin());
        i++;
    }*/

    Parse(power_data);
}

void LogReader::Parse(QStringList data)
{
    qDebug() << "Parse start from " << m_current_line;
    int i = m_current_line;
    while( i != data.size())
    {
        QString line = data.at(i);
        line = line.mid( line.indexOf("-")+1 ).trimmed();
        if (line.startsWith("GameEntity"))
        {
            QMap <QString, QString> map;

            map["type"] = "GAME_ENTITY";
            map["entity_id"] = Aquire(line, "EntityID=");

            int j = ++i;
            QString j_line = data.at(j);
            j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
            while (j_line.startsWith("tag="))
            {
                QString tag = Aquire( data.at(j), "tag=" );
                QString value = Aquire( data.at(j), "value=" );
                map[tag] = value;
                j = ++i;
                j_line = data.at(j);
                j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
            }
            ReportNewEntity( map );
            i = j;
        }
        else if (line.startsWith("Player"))
        {
            //new player or game
            QMap <QString, QString> map;
            map["type"] = "PLAYER";
            map["entity_id"] = Aquire(line, "EntityID=");
            map["player_id"] = Aquire(line, "PlayerID=");
            map["game_account_id"]= Aquire(line, "hi=") + QString("_") + Aquire(line, "lo=");

            int j = ++i;
            QString j_line = data.at(j);
            j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
            while (j_line.startsWith("tag="))
            {
                QString tag = Aquire( data.at(j), "tag=" );
                QString value = Aquire( data.at(j), "value=" );
                map[tag] = value;
                j = ++i;
                j_line = data.at(j);
                j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
            }
            ReportNewEntity( map );
            i = j;
        }
        else if (line.startsWith("FULL_ENTITY"))
        {
            if (line.contains("Updating"))
            {
                QString id = Aquire(line, "id=");

                int j = ++i;
                QString j_line = data.at(j);
                j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
                while (j_line.startsWith("tag="))
                {
                    QString tag = Aquire( data.at(j), "tag=" );
                    QString value = Aquire( data.at(j), "value=" );
                    emit EntityUpdate( id, tag, value );
                    j = ++i;
                    j_line = data.at(j);
                    j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
                }
                i = j;
            }
            else
            {
                //new entity
                QMap <QString, QString> map;
                map["cardtype"] = "CARD";
                map["entity_id"] = Aquire(line, "id=");
                map["cardid"] = Aquire(line, "cardId=");
                map["player"] = Aquire(line, "player=");

                int j = ++i;
                QString j_line = data.at(j);
                j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
                while (j_line.startsWith("tag="))
                {
                    QString tag = Aquire( data.at(j), "tag=" );
                    QString value = Aquire( data.at(j), "value=" );
                    map[tag] = value;
                    j = ++i;
                    j_line = data.at(j);
                    j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
                }
                ReportNewEntity( map );
                i = j;
            }
        }
        else if (line.startsWith("SHOW_ENTITY"))
        {
            //entity update
            QString entity_id = Aquire(line, "id=");

            QString card_id = Aquire(line, "cardId=");
            emit EntityUpdate(entity_id, "cardid", card_id);

            int j = ++i;
            QString j_line = data.at(j);
            j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
            while (j_line.startsWith("tag="))
            {
                QString tag = Aquire( data.at(j), "tag=" );
                QString value = Aquire( data.at(j), "value=" );
                emit EntityUpdate( entity_id, tag, value );
                j = ++i;
                j_line = data.at(j);
                j_line = j_line.mid( j_line.indexOf("-")+1 ).trimmed();
            }
            i = j;
        }
        else if (line.startsWith("TAG_CHANGE"))
        {
            //parse block data
            QString tag_name = Aquire(line, "tag=").toLower();
            QString value = Aquire( line, "value=" );
            if (line.contains("id="))
            {
                QString id = Aquire(line, "id=");
                emit EntityUpdate( id, tag_name, value );
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
    qDebug() << "Parse ends at " << m_current_line;
}

QString LogReader::Aquire(QString line, QString tag_name)
{
    //qDebug() << "Aquire " << tag_name << "in" << line;
    int begin = line.indexOf(tag_name, 0, Qt::CaseInsensitive);
    if (begin == -1)
        return "";
    else
        begin += tag_name.size();
    QString res = line.mid(begin, line.indexOf(" ", begin, Qt::CaseInsensitive) - begin);
    if (res.endsWith(']'))
        res.chop(1);
    //qDebug() << "RES: " << res;
    return res.trimmed();
}

void LogReader::ReportNewEntity( QMap<QString, QString>& data )
{
    //qDebug() << "LogReader::ReportNewEntity: " << data["entity_id"];
    Entity e;
    auto it = data.begin();
    while (it!=data.end())
    {
        e.AddTag(it.key(), it.value());
        it++;
    }

    emit NewEntity(e);
}
