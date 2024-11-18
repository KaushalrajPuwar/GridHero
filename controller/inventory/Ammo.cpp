#include "Ammo.h"

Ammo::Ammo(const std::string &name, int durability) : name(name), durability(durability) {}

void Ammo::use()
{
    if (durability > 0)
        --durability;
}

bool Ammo::isUsable() const
{
    return durability > 0;
}
