#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string &type) : type(type), x(0), y(0) {}

void Enemy::moveTowards(int heroX, int heroY)
{
    if (x < heroX)
        ++x;
    if (y < heroY)
        ++y;
    std::cout << type << " moved to (" << x << ", " << y << ")" << std::endl;
}

void Enemy::display() const
{
    std::cout << "Enemy: " << type << " at (" << x << ", " << y << ")" << std::endl;
}

// Add this method to reset the enemy's position
void Enemy::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
    std::cout << type << " position reset to (" << x << ", " << y << ")" << std::endl;
}