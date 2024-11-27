#include <iostream>
#include <vector>
#include "player/Player.h"
#include "enemy/Enemy.h"
#include "enemy/Dragon.h"
#include "inventory/Storage.h"
#include "inventory/Ammo.h"
#include "utilities/Grid.h"
#include "utilities/Position.h"

using namespace std;

int main()
{
    Player hero("Hero");
    Enemy enemy("Ogre");
    Storage storage;

    // Define available weapons
    Ammo sword("Sword", 5);
    Ammo stick("Stick", 5);
    Ammo dagger("Dagger", 30);
    Ammo clawHammer("Claw Hammer", 50);
    vector<Ammo> weapons = {stick, dagger, clawHammer};

    // Initialize the grid and set initial positions for hero and enemy
    vector<vector<int>> grid(10, vector<int>(10, 0));
    Grid::initializeGrid(grid);

    Position heroStart(9, 5);  // Bottom center
    Position enemyStart(0, 5); // Top center
    hero.move(heroStart, grid);
    enemy.setPosition(enemyStart);

    int level = 1;

    while (level <= 3)
    {
        if (level == 1)
        {
            std::cout << "Level 1: Avoid the enemy on the grid!" << std::endl;
            hero.playLevel1(enemy, storage, grid);

            if (storage.getBuildings() >= 3)
                level++;
        }
        else if (level == 2)
        {
            std::cout << "Level 2: Avoid the enemy with restricted areas!" << std::endl;
            hero.playLevel2(enemy, storage, sword, grid);

            if (storage.hasItem("Sword"))
                level++;
        }
        else if (level == 3)
        {
            std::cout << "Level 3: Welcome to the Dragon Slayer game!\n"
                      << std::endl;
            Dragon dragon("Dragon", 300, 20, "Fire Dragon");
            hero.startgame(dragon, hero, weapons, grid);
            break;
        }
    }

    // Final game outcome based on hero's health and dragon status
    if (hero.isAlive() && level == 3)
    {
        std::cout << "Congratulations! You defeated the dragon and won the game!" << std::endl;
    }
    else
    {
        std::cout << "Game over. Better luck next time!" << std::endl;
    }

    return 0;
}
