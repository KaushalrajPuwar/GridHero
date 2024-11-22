#include "Player.h"
#include "./enemy/Dragon.h"
#include <bits/stdc++.h>
using namespace std;

Player::Player(const std::string &name) : name(name), health(100),coins(0),xp(0),currentWeapon(0) {
    inventory={"stick"};
}

void Player::earnCoins(int amount)
{
    coins += amount;
}

int Player::getCoins() const
{
    return coins;
}
int Player::gethealth(){
    return health;
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

void Player::playLevel3(Dragon &dragon,Player &player,vector<Ammo>&weapons)
{
    cout<<"You are fighting"<<dragon.getName()<<"!\n";
    //dragon.showStatus();
    while (!dragon.isDefeated() && player.isAlive())
    {
            cout<<"\n1.Attack\n2. Dodge\n3. Go to Store";
            int choice;
            cin>>choice;
            int count=0;
            switch(choice){
            case 1:
                //attack();
                int damage=rand()%30 + 10;
                dragon.takeDamage(damage);
                cout<<"you attacked the dragon for"<<damage<<" damge.\n";
                break;
            case 2:
                //dodge();
                if(count ==rand()%5){
                dragon.takeDamage(3);
                }
                cout<<"You dodged the dragon's attack";//sword.use();
                count++;
                break;
            case 3:
                player.gotoStore(weapons,player);
                break;
            default:
                cout<<"invalid choice.Try again.\n";
            }
            if(!dragon.isDefeated() && player.isAlive()){
                int damage=dragon.getdamage();
                player.takeDamage(damage);
                cout<<"the dragon attacked you for"<<damage<<" damage.\n";
                //player.showStatus();
                //dragonAttack();
            }
            player.showStatus();
            dragon.showStatus();
    }
    if(player.isAlive()){
        cout<<"You defeated the dragon!\n";
        player.gainXP(50);
        player.earnCoins(100);
    }
    else{
        cout<<"The dragon defeated you.Game over.\n";
    }
            
        
        //sword.use();
    }
void Player:: showStatus(){
        cout<<"Player status"<<endl;
        cout << "XP: " << xp << ", Health: " << health << ", Gold coins: " << coins << endl;
        cout << "Current Weapon: " << inventory[currentWeapon] << endl;
        cout << "Inventory: ";
        for (const string& item : inventory) cout << item << " ";
        cout << endl;
}
void Player::startgame(Dragon &dragon,Player &player,vector<Ammo>&weapons){
    cout<<"FIGHT THE DRAGON"<<endl;
    while(true){
        player.showStatus();
        cout<<"Where would you like to go?\n1. Fight Dragon\n2. Go to store\n 3.Go to Cave\n";
        int choice;
        cin>>choice;
        if(choice==1){
            player.playLevel3(dragon,player,weapons);
        }
        else if(choice==2){
            player.gotoStore(weapons,player);
            //player.addWeapon(weapons);
            break;
        }
        else if(choice==3){
            player.gotoCave(weapons,player);
        }
        else{
            cout<<"invalid choice.Try again.\n";
        }
    }
}
 void Player::addWeapon(vector<Ammo>&weapons) {
        if (currentWeapon < weapons.size() - 1 && coins >= 30) {
            coins -= 30;
            currentWeapon++;
            inventory.push_back(weapons[currentWeapon].getName());
            cout << "You bought a " << weapons[currentWeapon].getName() << ".\n";
        } else if (currentWeapon == weapons.size() - 1) {
            cout << "You already have the most powerful weapon!\n";
        } else {
            cout << "Not enough gold.\n";
        }
    }
void Player::gotoStore(vector<Ammo>&weapons,Player &player){
        cout << "Welcome to the store. What would you like to do?\n";
        cout << "1. Buy 10 health points(10 gold)\n2. Buy weapon (30 gold)\n";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            player.buyHealth();
            
            break;
        case 2:
            player.addWeapon(weapons);
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
void Player::gotoCave(vector<Ammo>&weapons,Player &player){
       cout << "Welcome to the cave. Who would you like to fight?\n";
        cout << "1. Slime\n2. Fanged Beast\n";
        Dragon slime=slime=Dragon("Dragon",200,13,"slime");
        Dragon fangedBeast=Dragon("Dragon",500,80,"Fanged Beast");

        int choice;
        cin >> choice;

        switch (choice) {

        case 1:
            //slime=Dragon("Dragon",200,13,"slime");
            player.playLevel3(slime,player,weapons);
            break;
        case 2:
            //fangedBeast=Dragon("Dragon",500,80,"Fanged Beast");
            player.playLevel3(fangedBeast,player,weapons);
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    void Player::buyHealth(){
        if(coins>=10){
            losecoins(10);
            health+=10;
            cout<<"You bought 10 health.Current health: "<<health<<endl;
        }
        else{
            cout<<"not enough gold coins.\n";
        }
    }


void Player::takeDamage(int damage){
    health-=damage;
    if(health<0){
        health=0;
    }
}
/*void Player:: addWeapon(const string&weapon){
    inventory.push_back(weapon);
}*/
/*void Player::changeWeapon(const string&weapon){
    currentWeapon=weapon;
}*/
void Player::losecoins(int amount){
    coins=(coins>=amount)? (coins-amount):0;
}
void Player::gainXP(int amount){
    xp+=amount;
}
bool Player::isAlive() const{
    return health>0;
}
