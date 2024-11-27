#include "Player.h"
#include "../../controller/utilities/Grid.h"
#include "../../controller/utilities/Position.h"
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>

using namespace std;

Player::Player(const string &name)
    : name(name), coins(0), xp(0), health(100), currentWeapon(0), position(9, 4)
{
    // Initialize the inventory with "Stick" as the starting weapon
    inventory.push_back("Stick");
    visitedCells.insert(position); // Mark the starting position as visited
}

void Player::earnCoins(int amount)
{
    coins += amount;
}

int Player::getCoins() const
{
    return coins;
}

int Player::gethealth()
{
    return health;
}

void Player::move(Position newPos, vector<vector<int>> &grid)
{
    if (visitedCells.find(newPos) != visitedCells.end())
    {
        cout << "You cannot revisit this cell!" << endl;
        return;
    }

    position = newPos;
    visitedCells.insert(newPos);
    earnCoins(100); // Earn coins per movement
    cout << "Moved to position (" << position.x << ", " << position.y << ")" << endl;
}

void Player::playLevel1(Enemy &enemy, Storage &storage, vector<vector<int>> &grid)
{
    Position start = position;
    Position end = {0, 4};

    vector<Position> path = Grid::findPath(start, end, grid);
    for (const auto &step : path)
    {
        move(step, grid);
    }

    storage.addItem("Building", 3);
    cout << "Level 1 complete! Coins: " << getCoins() << endl;
}

void Player::playLevel2(Enemy &enemy, Storage &storage, Ammo &sword, vector<vector<int>> &grid)
{
    Position start = position;
    Position end = {0, 4};

    vector<Position> path = Grid::findPath(start, end, grid);
    for (const auto &step : path)
    {
        move(step, grid);
    }

    storage.addItem("Sword", 1);
    cout << "Level 2 complete! Coins: " << getCoins() << endl;
}

void Player::playLevel3(Dragon &dragon, Player &player, vector<Ammo> &weapons)
{
    cout << "You are fighting " << dragon.getName() << "!\n";
    int count = 0;

    while (!dragon.isDefeated() && player.isAlive())
    {
        cout << "\n1. Attack\n2. Dodge\n3. Go to Store\n";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            dragon.takeDamage(rand() % 30 + 10);
            break;
        case 2:
            if (count == rand() % 5)
                dragon.takeDamage(3);
            count++;
            break;
        case 3:
            player.gotoStore(weapons, player);
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

        if (!dragon.isDefeated() && player.isAlive())
        {
            player.takeDamage(dragon.getdamage());
        }
        player.showStatus();
        dragon.showStatus();
    }

    if (player.isAlive())
    {
        cout << "You defeated the dragon!\n";
        player.gainXP(50);
        player.earnCoins(100);
    }
    else
    {
        cout << "The dragon defeated you.\n";
    }
}

void Player::showStatus()
{
    cout << "XP: " << xp << ", Health: " << health << ", Coins: " << coins << endl;
    cout << "Weapon: " << inventory[currentWeapon] << endl;
}

void Player::startgame(Dragon &dragon, Player &player, vector<Ammo> &weapons, vector<vector<int>> &grid)
{
    while (true)
    {
        cout << "Where would you like to go?\n1. Fight Dragon\n2. Go to Store\n3. Go to Cave\n";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            player.playLevel3(dragon, player, weapons);
            break;
        case 2:
            player.gotoStore(weapons, player);
            break;
        case 3:
            player.gotoCave(weapons, player);
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void Player::addWeapon(vector<Ammo> &weapons)
{
    if (static_cast<size_t>(currentWeapon) < weapons.size() - 1 && coins >= 30)
    {
        coins -= 30;
        currentWeapon++;
        inventory.push_back(weapons[currentWeapon].getName());
    }
    else
    {
        cout << "Not enough gold or already max weapon.\n";
    }
}

void Player::gotoStore(vector<Ammo> &weapons, Player &player)
{
    cout << "Store options:\n1. Buy Health (10 coins)\n2. Buy Weapon (30 coins)\n";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        buyHealth();
        break;
    case 2:
        addWeapon(weapons);
        break;
    default:
        cout << "Invalid option!\n";
    }
}

void Player::gotoCave(vector<Ammo> &weapons, Player &player)
{
    cout << "Welcome to the cave. Who would you like to fight?\n";
    cout << "1. Slime\n2. Fanged Beast\n";
    Dragon slime = slime = Dragon("Dragon", 200, 13, "slime");
    Dragon fangedBeast = Dragon("Dragon", 500, 80, "Fanged Beast");

    int choice;
    cin >> choice;

    switch (choice)
    {

    case 1:
        // slime=Dragon("Dragon",200,13,"slime");
        player.playLevel3(slime, player, weapons);
        break;
    case 2:
        // fangedBeast=Dragon("Dragon",500,80,"Fanged Beast");
        player.playLevel3(fangedBeast, player, weapons);
        break;

    default:
        cout << "Invalid choice. Try again.\n";
    }
}

void Player::buyHealth()
{
    if (coins >= 10)
    {
        coins -= 10;
        health += 10;
    }
    else
    {
        cout << "Not enough coins!\n";
    }
}

void Player::takeDamage(int damage)
{
    health -= damage;
    if (health <= 0)
    {
        health = 0;
    }
}

bool Player::isAlive() const
{
    return health > 0;
}
