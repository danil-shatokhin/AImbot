#include "entitymanager.h"

inline bool sort_by_zone_pos(Entity &e1, Entity &e2)
{
    return e1.GetTag("zone_position") < e2.GetTag("zone_position");
}

EntityManager::EntityManager() :
    m_deathwing_account_id("144115198130930503_19625017"),
    m_turn_counter(0)
{

}

void EntityManager::Clear()
{
    m_game_entity = Entity();
    m_ally_hero = Entity();
    m_enemy_hero = Entity();
    m_entities.clear();
}

void EntityManager::NewEntity(Entity e)
{
    //qDebug() << "New" << e.GetTag("entity_id");
    if (e.GetTag("type") == "GAME")
    {
        m_game_entity = e;
    }
    else if (e.GetTag("type") == "PLAYER")
    {
        if (e.GetTag("game_account_id") == m_deathwing_account_id)
        {
            m_ally_hero = e;
        }
        else
        {
            m_enemy_hero = e;
        }
    }
    else
    {
        m_entities.push_back(e);
    }
}

void EntityManager::EntityUpdate(QString id, QString tag, QString new_value)
{
    qDebug() << "ENTITY UPDATE" << id << tag << new_value;
    for (int i=0; i<m_entities.size(); i++)
    {
        if (m_entities[i].id() == id)
        {
            m_entities[i].AddTag(tag, new_value);
            return;
        }
    }
}

void EntityManager::GlobalEntityUpdate(QString name, QString tag, QString value)
{
    //qDebug() << name << tag << value;
    if (name == "gameentity")
    {
        if (tag == "turn")
        {
            if (value.toInt() > m_turn_counter)
            {
                emit TurnStart( (value.toInt() + (m_ally_hero.GetTag("first_player") == "1"))%2 == 0 );
                    m_turn_counter = value.toInt();
            }
        }

        if (m_game_entity.GetTag("state") == "complete")
        {
            Clear();
            emit GameOver();
        }

        m_game_entity.AddTag(tag, value);
    }
    else if (name == "deathwing")
    {
        m_ally_hero.AddTag(tag, value);
    }
    else
    {
        m_enemy_hero.AddTag(tag, value);
    }
}

Entity EntityManager::GetAllyHero()
{
    return m_ally_hero;
}

Entity EntityManager::GetEnemyHero()
{
    return m_enemy_hero;
}

Entity EntityManager::GetGameEntity()
{
    return m_game_entity;
}

QVector<Entity> EntityManager::GetAllyHand()
{
    qDebug() << "ALLY HAND";
    QVector<Entity> res;
    QString ally_id = m_ally_hero.GetTag("controller");
    for (int i=0; i<m_entities.size(); i++)
    {
        if (m_entities[i].GetTag("controller") == ally_id && m_entities[i].GetTag("zone")=="hand")
        {
            res.push_back(m_entities[i]);
            qDebug() << m_entities[i].GetTag("entity_id") << m_entities[i].GetTag("controller") << m_entities[i].GetTag("zone");
        }
    }
    std::sort(res.begin(), res.end(), sort_by_zone_pos);
    return res;
}

QVector<Entity> EntityManager::GetAllyBoard()
{
    QVector<Entity> res;
    QString ally_id = m_ally_hero.GetTag("controller");
    for (int i=0; i<m_entities.size(); i++)
    {
        if (m_entities[i].GetTag("controller") == ally_id && m_entities[i].GetTag("zone")=="play" && m_entities[i].GetTag("cardtype")!="enchantment")
            res.push_back(m_entities[i]);
    }
    std::sort(res.begin(), res.end(), sort_by_zone_pos);
    return res;
}

QVector<Entity> EntityManager::GetEnemyHand()
{
    QVector<Entity> res;
    QString enemy_id = m_enemy_hero.GetTag("controller");
    for (int i=0; i<m_entities.size(); i++)
    {
        if (m_entities[i].GetTag("controller") == enemy_id && m_entities[i].GetTag("zone")=="hand")
            res.push_back(m_entities[i]);
    }
    std::sort(res.begin(), res.end(), sort_by_zone_pos);
    return res;
}

QVector<Entity> EntityManager::GetEnemyBoard()
{
    QVector<Entity> res;
    QString enemy_id = m_enemy_hero.GetTag("controller");
    for (int i=0; i<m_entities.size(); i++)
    {
        if (m_entities[i].GetTag("controller") == enemy_id && m_entities[i].GetTag("zone")=="play" && m_entities[i].GetTag("cardtype")!="enchantment")
            res.push_back(m_entities[i]);
    }
    std::sort(res.begin(), res.end(), sort_by_zone_pos);
    return res;
}
