#include "Player.h"
#include <iostream>

Player::Player(const std::string &name) : name(name), coins(0) {}

void Player::earnCoins(int amount)
{
    coins += amount;
}

int Player::getCoins() const
{
    return coins;
}

void Player::playLevel1(Enemy &enemy, Storage &storage)
{
    // Simple loop for demonstration (replace with actual grid logic)
    for (int steps = 0; steps < 10; ++steps)
    {
        earnCoins(100);
        enemy.moveTowards(steps, steps);
    }
    storage.addItem("Building", 3);
    std::cout << "Level 1 complete! Coins: " << getCoins() << std::endl;
}

void Player::playLevel2(Enemy &enemy, Storage &storage, Ammo &sword)
{
    enemy.setPosition(0, 0);
    
    for (int steps = 0; steps < 10; ++steps)
    {
        earnCoins(100);
        enemy.moveTowards(steps, steps); // Simulate grid with restricted areas
    }
    storage.addItem("Sword", 1);
    std::cout << "Level 2 complete! Coins: " << getCoins() << std::endl;
}

void Player::playLevel3(Dragon &dragon, Ammo &sword)
{
    while (!dragon.isDefeated() && sword.isUsable())
    {
        dragon.takeDamage(1);
        sword.use();
    }
}
