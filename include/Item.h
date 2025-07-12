#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Item : public Object
{
private:
    int health, attack, defense;
    int price;
    int nutritionalValue;
    int poisonPotency;
    int poisonDuration;
    bool isPoisonous;
    bool isDetoxifier;
    int detoxifyEffect;

public:
    Item();
    Item(string);
    ~Item();

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object *) override;

    bool operator==(const Item &other) const;

    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    int getPrice();
    int getNutritionalValue();
    int getPoisonPotency();
    int getPoisonDuration();
    int getDetoxifyEffect();
    bool IsPoisonous();
    bool IsDetoxifier();

    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setPrice(int);
    void setNutritionalValue(int);
    void setPoisonPotency(int);
    void setPoisonDuration(int);
    void setDetoxifyEffect(int);
    void setIsPoisonous(bool);
    void setIsDetoxifier(bool);
};

#endif // ITEM_H_INCLUDED
