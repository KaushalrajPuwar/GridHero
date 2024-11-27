#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "../../controller/utilities/Position.h"

class Enemy
{
protected:
    std::string name;
    std::string type;
    int health;
    Position position; // Use Position object for storing position

public:
    Enemy(const std::string &name, int health = 100);

    void setPosition(const Position &pos); // Accept Position object
    Position getPosition() const;

    void moveTowards(const Position &target, const std::vector<std::vector<int>> &grid);

    bool isAlive() const { return health > 0; }
};

#endif
