#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../inventory/Storage.h"
#include "../enemy/Enemy.h"
#include "../enemy/Dragon.h"
#include "../inventory/Ammo.h"

class Player
{
    std::string name;
    int coins;

public:
    Player(const std::string &name);

    void playLevel1(Enemy &enemy, Storage &storage);
    void playLevel2(Enemy &enemy, Storage &storage, Ammo &sword);
    void playLevel3(Dragon &dragon, Ammo &sword);

    void earnCoins(int amount);
    int getCoins() const;
};

#endif
