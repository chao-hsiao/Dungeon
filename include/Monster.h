#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;

class Monster : public GameCharacter
{
private:
    bool isBoss;
    int poisonPotency;
    int poisonDuration;
    bool isPoisonous;
    void showStatus() override;

public:
    Monster();
    Monster(bool);
    ~Monster();

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object *) override;

    /* Set & Get function*/
    int getPoisonPotency();
    int getPoisonDuration();
    bool getIsPoisonous();
    bool IsBoss();

    void setPoisonPotency(int);
    void setPoisonDuration(int);
    void setIsPoisonous(bool);
    void setIsBoss(bool);
};

#endif // ENEMY_H_INCLUDED
