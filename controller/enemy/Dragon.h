#ifndef DRAGON_H
#define DRAGON_H

#include "Enemy.h"

class Dragon : public Enemy
{
    int health;

public:
    Dragon(const std::string &type);
    void takeDamage(int damage);
    bool isDefeated() const;
};

#endif
