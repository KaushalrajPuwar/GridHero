#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy
{
protected:
    std::string type; // Make this protected so derived classes can access it
    int x, y;         // Position of the enemy on the grid

public:
    // Constructor
    Enemy(const std::string &type);

    // Methods
    void moveTowards(int heroX, int heroY); // Move towards the hero
    void display() const;                   // Display enemy's position
    void setPosition(int newX, int newY);   // Reset position to (newX, newY)
};

#endif // ENEMY_H
