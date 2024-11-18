#ifndef AMMO_H
#define AMMO_H

#include <string>

class Ammo
{
    std::string name;
    int durability;

public:
    Ammo(const std::string &name, int durability);
    void use();
    bool isUsable() const;
};

#endif
