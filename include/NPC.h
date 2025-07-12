#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class NPC : public GameCharacter
{
private:
    vector<Item> commodity;
    void showStatus() override;

public:
    NPC();           // generate a random values NPC with commodity
    NPC(bool clean); // generate a NPC with no commodity
    ~NPC();

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object *) override;
    void listCommodity(); /*print all the Item in this NPC*/
    void addCommodity(Item);

    /* Set & Get function*/
    void setCommodity(vector<Item>);
    vector<Item> getCommodity();
};

#endif // NPC_H_INCLUDED
