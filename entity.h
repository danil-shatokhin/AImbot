#ifndef ENTITY_H
#define ENTITY_H
#include <QString>

class Entity
{
    enum Field
    {
        Field_ZONE,
        Field_POSITION,
        Field_ATK_THIS_TURN,
        Field_DAMAGE
    };

    enum Type
    {
        Type_INVALID,
        Type_MINION,
        Type_SPELL,
        Type_SECRET,
        Type_PLAYER
    };

    enum Owner
    {
        Owner_Ally,
        Owner_Enemy,
        Owner_count
    };



    enum Zone
    {
        Zone_Deck,
        Zone_Hand,
        Zone_Play,
        Zone_Graveyard,
        Zone_count
    };

    QMap<QString, QString> m_additional_data;
    int m_id;
    Owner m_owner;
    Zone m_zone;
    int attack_this_turn;
    QString m_name;
    int m_max_health;
    int m_damage;
    int m_damage_taken;

public:
    Entity();
    int id() const;
    void setId(int id);
    Owner owner() const;
    void setOwner(const Owner &owner);
    Zone zone() const;
    void setZone(const Zone &zone);
    int getAttackThisTurn() const;
    void setAttackThisTurn(int value);
    QString getName() const;
    void setName(const QString &name);
    int getMax_health() const;
    int getDamage() const;
    int getCurrentHealth() const;
    //void setDamageTaken(int damage_taken);
    void AddTag( QString tag, QString value );
};

#endif // ENTITY_H
