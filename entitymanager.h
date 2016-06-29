#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <entity.h>
#include <QVector>
#include <QDebug>
#include <QObject>

class EntityManager : public QObject
{
    Q_OBJECT

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

    void Clear();
    void NewEntity(Entity e);
    void EntityUpdate( QString id, QString tag, QString new_value );
    void GlobalEntityUpdate( QString name, QString tag, QString value );

signals:
    void TurnStart(bool my_turn);
    void TurnOver();
};

#endif // ENTITYMANAGER_H
