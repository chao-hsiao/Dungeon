#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Animal.h"

using namespace std;

static int currentRoomIndex;
static int previousRoomIndex;
static vector<int> upRoomIndex;
static vector<int> downRoomIndex;
static vector<int> leftRoomIndex;
static vector<int> rightRoomIndex;

/* This is the record system. Get the information of the  */
/* player and rooms then save them to (a) file(s). Notice */
/* that using pass by reference can prevent sending the   */
/* whole vector to the function.                          */

class Record
{
private:
    void savePlayer(Player *, ofstream &);
    void saveRooms(vector<Room> &, ofstream &);
    void loadPlayer(Player *, ifstream &);
    void loadRooms(vector<Room> &, ifstream &);

public:
    Record();
    void saveToFile(Player *, vector<Room> &);
    void loadFromFile(Player *, vector<Room> &);
};

#endif // RECORD_H_INCLUDED
