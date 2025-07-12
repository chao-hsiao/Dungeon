#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "NPC.h"

using namespace std;

class Animal : public GameCharacter
{
private:
    void showStatus() override;
    int attackChance;
    int wantToFight;

public:
    Animal();
    Animal(string);
    ~Animal();

    bool triggerEvent(Object *) override;

    /* Set & Get function*/
    bool getWantToFight();
    int getAttackChance();

    void setAttackChance(int);
    void setWantToFight(bool);
};

#endif // ANIMAL_H_INCLUDED