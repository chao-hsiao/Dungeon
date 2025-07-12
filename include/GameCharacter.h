#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter : public Object
{
private:
    // string name;
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
    int dodgeChance;
    int gold;
    string script;

public:
    GameCharacter();
    GameCharacter(string, string, string, int, int, int, int);
    virtual ~GameCharacter();

    bool checkIsDead();
    int takeDamage(int);
    virtual void showStatus() = 0;

    /* Set & Get function*/
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setDodgeChance(int);
    void setGold(int);
    void setScript(string);

    int getMaxHealth();
    int getCurrentHealth();
    int getAttack();
    int getDefense();
    int getDodgeChance();
    int getGold();
    string getScript();
};
#endif // GAMECHARACTER_H_INCLUDED
