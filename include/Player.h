#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Monster.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;
class Room;

class Player : public GameCharacter
{
private:
    Room *currentRoom;
    Room *previousRoom;
    vector<Item> inventory;
    vector<Item> equippedItems;
    int thirst;
    int maxThirst;
    int hunger;
    int maxHunger;
    bool isPoison;
    int poisonLevel;
    int poisonDuration;
    int buff;
    int debuff;
    static int roundCount;
    bool ignoreUpdate;
    bool ignoreCompletelyUpdate;

    void showStatus() override;

public:
    Player();
    Player(string, string, int, int, int, int);
    ~Player();

    void increaseStates(int health, int attack, int defense);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object *) override;
    void updateStatus();
    void changeRoom(Room *);
    void addItem(Item);
    void addEquippedItem(Item);
    bool hasItem(string);
    bool hasTypeInInventory(string);
    void setIgnoreUpdate();
    void setIgnoreCompletelyUpdate();
    int takeDamage(int); // redefine takeDamage function

    void useItem();
    void equipItem();
    void equipItem(Item);
    void unequipItem();
    void unequipItem(Item);
    void eat(Item);
    void drink(Item);
    void detoxify(Item);
    void applyPoison(int potency, int duration);

    void increaseHunger(int amount);
    void decreaseHunger(int amount);
    void increaseThirst(int amount);
    void decreaseThirst(int amount);
    void restoreThirst();
    void applyHealthChange(int change);
    void applyDebuff(int severity);
    void applyBuff(int bonus);

    int getEffectiveAttack();
    int getEffectiveDefense();

    /* Set & Get function*/
    void setCurrentRoom(Room *);
    void setPreviousRoom(Room *);
    void setInventory(vector<Item>);
    void setThirst(int);
    void setMaxThirst(int);
    void setHunger(int);
    void setMaxHunger(int);
    void setIsPoison(bool);
    void setPoisonLevel(int);
    void setPoisonDuration(int);
    void setBuff(int);
    void setDebuff(int);

    Room *getCurrentRoom();
    Room *getPreviousRoom();
    vector<Item> getInventory();
    vector<Item> getequippedItems();
    int getThirst();
    int getMaxThirst();
    int getHunger();
    int getMaxHunger();
    bool IsPoison();
    int getPoisonLevel();
    int getPoisonDuration();
    int getBuff();
    int getDebuff();
};

#endif // PLAYER_H_INCLUDED
