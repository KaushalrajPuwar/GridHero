#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string &name, int health) : name(name), health(health), position(0, 0) {}

void Enemy::setPosition(const Position &pos)
{
    position = pos;
}

Position Enemy::getPosition() const
{
    return position;
}

void Enemy::moveTowards(const Position &target, const std::vector<std::vector<int>> &grid)
{
    // Implementation to move enemy using grid pathfinding
    std::cout << name << " is moving towards target at (" << target.x << ", " << target.y << ").\n";
}
