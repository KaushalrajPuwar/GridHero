#include "Dragon.h"
#include <iostream>

Dragon::Dragon(const std::string &type) : Enemy(type), health(5) {}

void Dragon::takeDamage(int damage)
{
    health -= damage;
    std::cout << type << " took " << damage << " damage! Health: " << health << std::endl;
}

bool Dragon::isDefeated() const
{
    return health <= 0;
}
