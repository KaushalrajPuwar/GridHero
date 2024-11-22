#include <iostream>
#include "player/Player.h"
#include "enemy/Enemy.h"
#include "enemy/Dragon.h"
#include "inventory/Storage.h"
#include "inventory/Ammo.h"

int main()
{
    Player hero("Hero");
    Enemy enemy("Ogre");
    
    Storage storage;
    Ammo sword("sword",5);
    Ammo stick("Stick", 5);
    Ammo dagger("Dagger",30);
    Ammo clawHammer("Claw Hammer",50);
    vector<Ammo>weapons={stick,dagger,clawHammer};

    int level = 1;

    while (level <= 3)
    {
        if (level == 1)
        {
            std::cout << "Level 1: Avoid the enemy on the grid!" << std::endl;
            hero.playLevel1(enemy, storage);
            if (storage.getBuildings() >= 3)
                level++;
        }
        else if (level == 2)
        {
            std::cout << "Level 2: Avoid the enemy with restricted areas!" << std::endl;
            hero.playLevel2(enemy, storage, sword);
            if (storage.hasItem("Sword"))
                level++;
        }
        else if (level == 3)
        {
            std::cout << "Level 3: Welcome to the Dragon Slayer game!\n" << std::endl;
            Dragon dragon("Dragon",300,20,"Fired Dragon");
            hero.startgame(dragon,hero,weapons);
            break;
        }
    }
    

    /*if (dragon.isDefeated())
    {
        std::cout << "Congratulations! You defeated the dragon and won the game!" << std::endl;
    }
    else
    {
        std::cout << "Game over. Better luck next time!" << std::endl;
    }*/

    return 0;
}
