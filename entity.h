#ifndef ENTITY_H
#define ENTITY_H
#include <QString>
#include <QMap>

class Entity
{
private:
    QMap<QString, QString> m_tags;

public:
    Entity();
    QString id() const;
    QString card_id() const;
    QString owner() const;
    QString zone() const;
    int getAttackThisTurn() const;
    QString getName() const;
    int getMax_health() const;
    int getDamage() const;
    int getCurrentHealth() const;
    //void setDamageTaken(int damage_taken);
    void AddTag( QString tag, QString value );
    QString GetTag( QString key );
    QString GetInfo();
};

#endif // ENTITY_H
