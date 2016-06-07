#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <entity.h>
#include <QVector>
#include <QDebug>

class EntityManager
{
    const QString m_deathwing_account_id;
    QVector<Entity> m_entities;
    Entity m_game_entity;
    Entity m_ally_hero;
    Entity m_enemy_hero;

public:
    EntityManager();

    Entity GetAllyHero();
    Entity GetEnemyHero();
    Entity GetGameEntity();

    QVector<Entity> GetAllyHand();
    QVector<Entity> GetAllyBoard();
    QVector<Entity> GetEnemyHand();
    QVector<Entity> GetEnemyBoard();

    //bool sort_by_zone_pos(const Entity& e1, const Entity& e2);

    void Clear();
    void NewEntity(Entity e);
    void EntityUpdate( QString id, QString tag, QString new_value );
    void GlobalEntityUpdate( QString name, QString tag, QString value );
};

#endif // ENTITYMANAGER_H
