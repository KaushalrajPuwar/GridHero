#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include<bits/stdc++.h>
using namespace std;
#include "../inventory/Storage.h"
#include "../enemy/Enemy.h"
#include "../enemy/Dragon.h"
#include "../inventory/Ammo.h"

class Player
{
    private:
    string name;
    int coins;
    int xp;
    int health;
    int currentWeapon;
    vector<string>inventory;

public:
    Player(const std::string &name);

    void playLevel1(Enemy &enemy, Storage &storage);
    void playLevel2(Enemy &enemy, Storage &storage, Ammo &sword);
    void playLevel3(Dragon &dragon, Player &player,vector<Ammo>&weapons);

    string getname();
    void startgame(Dragon &dragon,Player &player,vector<Ammo>&weapons);
    void buyHealth();
    void showStatus();
    int getxp();
    int getcurrentWeapon();
    int gethealth();
    void takeDamage(int damage);
    void gotoStore(vector<Ammo>&weapons,Player &player);
    void addWeapon(vector<Ammo>&weapons);
    void changeWeapon(const string&weapon);
    void earnCoins(int amount);
    int getCoins() const;
    void losecoins(int amount);
    void gainXP(int amount);
    bool isAlive() const;
    void gotoCave(vector<Ammo>&weapons,Player &player);
};

#endif
