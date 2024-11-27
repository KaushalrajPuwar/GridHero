#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <set>
#include "../../controller/utilities/Position.h" // Include Position for player's position tracking
#include "Enemy.h"
#include "Storage.h"
#include "Ammo.h"
#include "Dragon.h"
using namespace std;

class Player
{
private:
    string name;
    int coins;
    int xp;
    int health;
    int currentWeapon;
    vector<string> inventory;
    Position position;          // Track player's current position
    set<Position> visitedCells; // Track visited cells

public:
    Player(const string &name);

    void earnCoins(int amount);
    int getCoins() const;
    int gethealth();
    void move(Position newPos, vector<vector<int>> &grid);
    void playLevel1(Enemy &enemy, Storage &storage, vector<vector<int>> &grid);
    void playLevel2(Enemy &enemy, Storage &storage, Ammo &sword, vector<vector<int>> &grid);
    void playLevel3(Dragon &dragon, Player &player, vector<Ammo> &weapons);
    void showStatus();
    void startgame(Dragon &dragon, Player &player, vector<Ammo> &weapons, vector<vector<int>> &grid);
    void addWeapon(vector<Ammo> &weapons);
    void gotoStore(vector<Ammo> &weapons, Player &player);
    void gotoCave(vector<Ammo> &weapons, Player &player); // Assume previously defined
    void buyHealth();
    void takeDamage(int damage);
    bool isAlive() const;
    void gainXP(int amount) { xp += amount; }
};

#endif
