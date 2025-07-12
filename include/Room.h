#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"

using namespace std;

class Room : public Object
{
private:
    Room *upRoom;
    Room *downRoom;
    Room *leftRoom;
    Room *rightRoom;
    bool isExit;
    int index;
    static int roomCount;
    static int sandstormDuration;
    static int chanceOfSandstorms;
    int chanceOfWaterSource;
    bool hasWaterSource;
    int chanceOfPoisonousWaterSource;
    bool WSisPoisonous;

    static bool hasSandstorm;
    static int hungerIncreaseRate;
    static int thirstIncreaseRate;
    static int hungerChanges;
    static int thirstChanges;
    vector<Object *> objects;

    bool ignoreUpdate;

public:
    Room();
    Room(bool, vector<Object *>, string tag);

    bool popObject(Object *); /*pop out the specific object, used when the interaction is done*/
    void addObject(Object *);
    void setIgnoreUpdate();
    string getWaterSourceName();
    void roomUpdateStatus();
    bool triggerEvent(Object *) override;

    /* Set & Get function*/
    void setUpRoom(Room *);
    void setDownRoom(Room *);
    void setLeftRoom(Room *);
    void setRightRoom(Room *);
    void setIsExit(bool);
    void setIndex(int);
    void setObjects(vector<Object *>);
    void setChanceOfSandstorms(int);
    void setChanceOfWaterSource(int);
    void setChanceOfPoisonousWaterSource(int);
    void setWSisPoisonous(bool);
    void setHasSandstorm(bool);
    void setHasWaterSource(bool);
    void setSandstormDuration(int);
    void setHungerChanges(int);
    void setThirstChanges(int);
    void setRoomCount(int);
    void setThirstIncreaseRate(int);
    void setHungerIncreaseRate(int);

    Room *getUpRoom();
    Room *getDownRoom();
    Room *getLeftRoom();
    Room *getRightRoom();
    vector<Object *> getObjects();
    bool IsExit();
    int getIndex();
    static int getRoomCount();
    static int getChanceOfSandstorms();
    int getChanceOfWaterSource();
    int getChanceOfPoisonousWaterSource();
    bool getWSisPoisonous();
    static bool HasSandstorm();
    bool HasWaterSource();
    static int getHungerIncreaseRate();
    static int getThirstIncreaseRate();
    static int getSandstormDuration();
    static int getHungerChanges();
    static int getThirstChanges();
};

#endif // ROOM_H_INCLUDED
