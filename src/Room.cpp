#include "Room.h"
#include "CommonFunc.h"

const string rooms_name[] = {"Dungeon", "Cave", "Castle", "Tower", "Maze", "Crypt", "Temple", "Ruins", "Tomb", "Fortress"};

int Room::sandstormDuration = 0;
int Room::chanceOfSandstorms = 0;
int Room::hungerIncreaseRate = 1;
int Room::thirstIncreaseRate = 1;
int Room::hungerChanges = 0;
int Room::thirstChanges = 0;
int Room::roomCount = 0;
bool Room::hasSandstorm = false;

Room::Room() : upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr) {}

Room::Room(bool isExit, vector<Object *> objects, string RoomSysType)
    : Object(rooms_name[rand() % (sizeof(rooms_name) / sizeof(rooms_name[0]))], "None"), upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr), isExit(isExit), index(roomCount++), hasWaterSource(false), WSisPoisonous(false), objects(objects), ignoreUpdate(false)
{
    setTag(RoomSysType);
    if (isExit)
        setName("Exit");
    if (index == 0)
        setName("Entrance");

    if (RoomSysType == "Desert")
    {
        chanceOfWaterSource = 8;
        chanceOfSandstorms = 15;
        chanceOfPoisonousWaterSource = 0;
        hungerChanges = 2;
        thirstChanges = 6;
    }
    else if (RoomSysType == "Forest")
    {
        chanceOfWaterSource = 70;
        chanceOfSandstorms = 0;
        chanceOfPoisonousWaterSource = 0;
        hungerChanges = 6;
        thirstChanges = 2;
    }
    else if (RoomSysType == "Swamp")
    {
        chanceOfWaterSource = 70;
        chanceOfSandstorms = 0;
        chanceOfPoisonousWaterSource = 20;
        hungerChanges = 2;
        thirstChanges = 3;
    }
    else
    {
        chanceOfWaterSource = 0;
        chanceOfSandstorms = 0;
        chanceOfPoisonousWaterSource = 0;
        hungerChanges = 1;
        thirstChanges = 1;
    }
    if (!isExit)
        hasWaterSource = rand() % 100 < chanceOfWaterSource;
}

bool Room::triggerEvent(Object *object)
{
    Player *p = dynamic_cast<Player *>(object);
    if (p == nullptr)
    {
        return false;
    }

    int choice;
    int dircount = 0;
    cout << "----------------- Directions ----------------" << endl;
    cout << "Where do you want to go?" << endl;
    if (p->getCurrentRoom()->getUpRoom() != nullptr)
    {
        cout << " " << ++dircount;
        if (p->getPreviousRoom() == p->getCurrentRoom()->getUpRoom())
            cout << ". Previous Room";
        cout << ". North to " << p->getCurrentRoom()->getUpRoom()->getName() << ".";
        cout << endl;
    }
    if (p->getCurrentRoom()->getRightRoom() != nullptr)
    {
        cout << " " << ++dircount;
        if (p->getPreviousRoom() == p->getCurrentRoom()->getRightRoom())
            cout << ". Previous Room";
        cout << ". East to " << p->getCurrentRoom()->getRightRoom()->getName() << ".";
        cout << endl;
    }
    if (p->getCurrentRoom()->getDownRoom() != nullptr)
    {
        cout << " " << ++dircount;
        if (p->getPreviousRoom() == p->getCurrentRoom()->getDownRoom())
            cout << ". Previous Room";
        cout << ". South to " << p->getCurrentRoom()->getDownRoom()->getName() << ".";
        cout << endl;
    }
    if (p->getCurrentRoom()->getLeftRoom() != nullptr)
    {
        cout << " " << ++dircount;
        if (p->getPreviousRoom() == p->getCurrentRoom()->getLeftRoom())
            cout << ". Previous Room";
        cout << ". West to " << p->getCurrentRoom()->getLeftRoom()->getName() << ".";
        cout << endl;
    }
    cout << " " << ++dircount << ". Stay in current room, " << p->getCurrentRoom()->getName() << "." << endl;
    cout << "---------------------------------------------" << endl
         << endl;

    choice = getUserChoice("Enter your choice", 1, dircount);

    if (p->getCurrentRoom()->getUpRoom() != nullptr && --choice == 0)
        p->changeRoom(p->getCurrentRoom()->getUpRoom());
    else if (p->getCurrentRoom()->getRightRoom() != nullptr && --choice == 0)
        p->changeRoom(p->getCurrentRoom()->getRightRoom());
    else if (p->getCurrentRoom()->getDownRoom() != nullptr && --choice == 0)
        p->changeRoom(p->getCurrentRoom()->getDownRoom());
    else if (p->getCurrentRoom()->getLeftRoom() != nullptr && --choice == 0)
        p->changeRoom(p->getCurrentRoom()->getLeftRoom());
    else if (--choice == 0)
    {
        cout << "You stay in " << p->getCurrentRoom()->getName() << "." << endl
             << endl;
        p->getCurrentRoom()->setIgnoreUpdate();
        p->setIgnoreCompletelyUpdate();
    }
    return true;
}

bool Room::popObject(Object *object)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i] == object)
        {
            objects.erase(objects.begin() + i);
            delete object;
            return true;
        }
    }
    return false;
}

void Room::setUpRoom(Room *room)
{
    this->upRoom = room;
    room->downRoom = this;
}

void Room::setDownRoom(Room *room)
{
    this->downRoom = room;
    room->upRoom = this;
}

void Room::setLeftRoom(Room *room)
{
    this->leftRoom = room;
    room->rightRoom = this;
}

void Room::setRightRoom(Room *room)
{
    this->rightRoom = room;
    room->leftRoom = this;
}

void Room::setIsExit(bool isExit)
{
    this->isExit = isExit;
}

void Room::setIndex(int index)
{
    this->index = index;
}

void Room::setObjects(vector<Object *> objects)
{
    this->objects = objects;
}

void Room::addObject(Object *object)
{
    objects.push_back(object);
}

bool Room::IsExit()
{
    return isExit;
}

int Room::getIndex()
{
    return index;
}

int Room::getRoomCount()
{
    return roomCount;
}

vector<Object *> Room::getObjects()
{
    return objects;
}

Room *Room::getUpRoom()
{
    return upRoom;
}

Room *Room::getDownRoom()
{
    return downRoom;
}

Room *Room::getLeftRoom()
{
    return leftRoom;
}

Room *Room::getRightRoom()
{
    return rightRoom;
}

string Room::getWaterSourceName()
{
    string waterSource;
    if ("Desert" == getTag())
    {
        waterSource = "an oasis";
    }
    else if ("Forest" == getTag())
    {
        waterSource = "a lake";
    }
    else if ("Swamp" == getTag())
    {
        waterSource = "a pond";
    }
    else
    {
        waterSource = "a water source";
    }
    return waterSource;
}

int Room::getChanceOfPoisonousWaterSource()
{
    return chanceOfPoisonousWaterSource;
}

bool Room::HasWaterSource()
{
    return hasWaterSource;
}

int Room::getHungerIncreaseRate()
{
    return hungerIncreaseRate;
}

int Room::getThirstIncreaseRate()
{
    return thirstIncreaseRate;
}

void Room::setHungerIncreaseRate(int rate)
{
    hungerIncreaseRate = rate;
}

int Room::getSandstormDuration()
{
    return sandstormDuration;
}

void Room::setThirstIncreaseRate(int rate)
{
    thirstIncreaseRate = rate;
}

int Room::getHungerChanges()
{
    return hungerChanges * hungerIncreaseRate;
}

int Room::getThirstChanges()
{
    return thirstChanges * thirstIncreaseRate;
}

void Room::roomUpdateStatus()
{
    if (ignoreUpdate)
    {
        ignoreUpdate = false;
        return;
    }
    if (getTag() == "Desert")
    {
        if (rand() % 100 < chanceOfSandstorms && sandstormDuration == 0 && !hasSandstorm)
        {
            cout << "You are in a sandstorm!" << endl;
            sandstormDuration = rand() % 5 + 2;
            hungerIncreaseRate = rand() % 3 + 2;
            hasSandstorm = true;
            cout << "The rate of hunger and thirst increase is " << hungerIncreaseRate << " times higher!" << endl
                 << endl;
        }
        if (sandstormDuration > 0)
        {
            sandstormDuration--;
            cout << "Sandstorm Duration: " << sandstormDuration << " turns left." << endl
                 << endl;

            if (sandstormDuration == 0 && hasSandstorm)
            {
                cout << "Sandstorm is over!" << endl
                     << endl;
                sandstormDuration = 0;
                hungerIncreaseRate = 1;
                hasSandstorm = false;
            }
        }
    }
}

void Room::setIgnoreUpdate()
{
    ignoreUpdate = true;
}

int Room::getChanceOfSandstorms()
{
    return chanceOfSandstorms;
}
int Room::getChanceOfWaterSource()
{
    return chanceOfWaterSource;
}
bool Room::getWSisPoisonous()
{
    return WSisPoisonous;
}
bool Room::HasSandstorm()
{
    return hasSandstorm;
}

void Room::setRoomCount(int count)
{
    roomCount = count;
}

void Room::setChanceOfSandstorms(int chance)
{
    chanceOfSandstorms = chance;
}

void Room::setChanceOfWaterSource(int chance)
{
    chanceOfWaterSource = chance;
}

void Room::setChanceOfPoisonousWaterSource(int chance)
{
    chanceOfPoisonousWaterSource = chance;
}

void Room::setWSisPoisonous(bool isPoisonous)
{
    WSisPoisonous = isPoisonous;
}

void Room::setHasSandstorm(bool hasSandstorm)
{
    this->hasSandstorm = hasSandstorm;
}

void Room::setHasWaterSource(bool hasWaterSource)
{
    this->hasWaterSource = hasWaterSource;
}

void Room::setSandstormDuration(int duration)
{
    sandstormDuration = duration;
}

void Room::setHungerChanges(int changes)
{
    hungerChanges = changes;
}

void Room::setThirstChanges(int changes)
{
    thirstChanges = changes;
}
