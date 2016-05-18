#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <entity.h>
#include <QVector>

class EntityManager
{
    QVector<Entity> m_entities;
public:
    EntityManager();
};

#endif // ENTITYMANAGER_H
