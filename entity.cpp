#include "entity.h"

QString Entity::id() const
{
    return m_tags["entity_id"];
}

QString Entity::card_id() const
{
    return m_tags["cardid"];
}

QString Entity::owner() const
{
    return m_tags["owner"];
}

QString Entity::zone() const
{
    return m_tags["zone"];
}

QString Entity::getName() const
{
    return m_tags["name"];
}

int Entity::getMax_health() const
{
    return m_tags["max_health"].toInt();
}

int Entity::getDamage() const
{
    return m_tags["damage_taken"].toInt();
}

int Entity::getCurrentHealth() const
{
    return m_tags["max_health"].toInt() - m_tags["damage_taken"].toInt();
}

void Entity::AddTag( QString tag, QString value )
{
    m_tags[tag] = value;
}

QString Entity::GetTag(QString key)
{
    return m_tags[key];
}

QString Entity::GetInfo()
{
    QString res;
    auto it = m_tags.begin();
    while (it!=m_tags.end())
    {
        res += it.key() + QString(": ") + it.value() + QString("\n");
        it++;
    }
    return res;
}

Entity::Entity()
{

}
