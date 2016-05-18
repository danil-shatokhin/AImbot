#include "entity.h"

int Entity::id() const
{
    return m_id;
}

void Entity::setId(int id)
{
    m_id = id;
}

Owner Entity::owner() const
{
    return m_owner;
}

void Entity::setOwner(const Owner &owner)
{
    m_owner = owner;
}

Zone Entity::zone() const
{
    return m_zone;
}

void Entity::setZone(const Zone &zone)
{
    m_zone = zone;
}

int Entity::getAttack_this_turn() const
{
    return attack_this_turn;
}

void Entity::setAttack_this_turn(int value)
{
    attack_this_turn = value;
}

QString Entity::getName() const
{
    return m_name;
}

void Entity::setName(const QString &name)
{
    m_name = name;
}

int Entity::getMax_health() const
{
    return m_max_health;
}

int Entity::getDamage() const
{
    return m_damage;
}

int Entity::getCurrentHealth() const
{
    return m_max_health - m_damage_taken;
}

Entity::Entity()
{

}
