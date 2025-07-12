#include "Record.h"

Record::Record() {}

void Record::saveToFile(Player *player, vector<Room> &rooms)
{
    ofstream file("save.txt");
    if (file.is_open())
    {
        savePlayer(player, file);
        saveRooms(rooms, file);
        file.close();
        cout << "Game saved!" << endl
             << endl;
    }
    else
    {
        cout << "Failed to save the game." << endl
             << endl;
    }
}

void Record::loadFromFile(Player *player, vector<Room> &rooms)
{
    ifstream file("save.txt");
    if (file.is_open())
    {
        loadPlayer(player, file);
        loadRooms(rooms, file);
        file.close();

        for (Room &room : rooms)
        {
            if (room.getIndex() == currentRoomIndex)
            {
                player->setCurrentRoom(&room);
            }
            if (room.getIndex() == previousRoomIndex)
            {
                player->setPreviousRoom(&room);
            }
        }
        for (Room &room : rooms)
        {
            int i = 0;
            for (Room &room2 : rooms)
            {
                if (room.getIndex() == upRoomIndex[i])
                {
                    room.setUpRoom(&room2);
                }
                if (room.getIndex() == downRoomIndex[i])
                {
                    room.setDownRoom(&room2);
                }
                if (room.getIndex() == leftRoomIndex[i])
                {
                    room.setLeftRoom(&room2);
                }
                if (room.getIndex() == rightRoomIndex[i])
                {
                    room.setRightRoom(&room2);
                }
                i++;
            }
        }
    }
    else
    {
        cout << "No save file found." << endl
             << endl;
    }
}

void Record::savePlayer(Player *player, ofstream &file)
{
    file << "#PLAYER" << endl;
    file << player->getName() << endl;
    file << player->getTag() << endl;
    file << player->getMaxHealth() << endl;
    file << player->getCurrentHealth() << endl;
    file << player->getAttack() << endl;
    file << player->getDefense() << endl;
    file << player->getDodgeChance() << endl;
    file << player->getGold() << endl;
    file << player->getScript() << endl;
    file << player->getThirst() << endl;
    file << player->getMaxThirst() << endl;
    file << player->getHunger() << endl;
    file << player->getMaxHunger() << endl;
    file << player->IsPoison() << endl;
    file << player->getPoisonLevel() << endl;
    file << player->getPoisonDuration() << endl;
    file << player->getBuff() << endl;
    file << player->getDebuff() << endl;
    if (player->getCurrentRoom() == nullptr)
        file << -1 << endl;
    else
        file << player->getCurrentRoom()->getIndex() << endl;
    if (player->getPreviousRoom() == nullptr)
        file << -1 << endl;
    else
        file << player->getPreviousRoom()->getIndex() << endl;

    file << "#INVENTORY" << endl;
    for (Item item : player->getInventory())
    {
        file << "#ITEM" << endl;
        file << item.getName() << endl;
        file << item.getTag() << endl;
        file << item.getAttack() << endl;
        file << item.getDefense() << endl;
        file << item.getHealth() << endl;
        file << item.getNutritionalValue() << endl;
        file << item.getPoisonPotency() << endl;
        file << item.getPoisonDuration() << endl;
        file << item.getDetoxifyEffect() << endl;
        file << item.getPrice() << endl;
        file << item.IsPoisonous() << endl;
        file << item.IsDetoxifier() << endl;
        file << "#endITEM" << endl;
    }
    file << "#endINVENTORY" << endl;
    file << "#EQUIPPEDITEMS" << endl;
    for (Item item : player->getequippedItems())
    {
        file << "#ITEM" << endl;
        file << item.getName() << endl;
        file << item.getTag() << endl;
        file << item.getAttack() << endl;
        file << item.getDefense() << endl;
        file << item.getHealth() << endl;
        file << item.getNutritionalValue() << endl;
        file << item.getPoisonPotency() << endl;
        file << item.getPoisonDuration() << endl;
        file << item.getDetoxifyEffect() << endl;
        file << item.getPrice() << endl;
        file << item.IsPoisonous() << endl;
        file << item.IsDetoxifier() << endl;
        file << "#endITEM" << endl;
    }
    file << "#endEQUIPPEDITEMS" << endl;
    file << "#endPLAYER" << endl;
}

void Record::saveRooms(vector<Room> &rooms, ofstream &file)
{
    file << "#ROOMS" << endl;
    for (Room &room : rooms)
    {
        file << "#ROOM" << endl;
        if (room.getUpRoom() == nullptr)
            file << -1 << endl;
        else
            file << room.getUpRoom()->getIndex() << endl;
        if (room.getDownRoom() == nullptr)
            file << -1 << endl;
        else
            file << room.getDownRoom()->getIndex() << endl;
        if (room.getLeftRoom() == nullptr)
            file << -1 << endl;
        else
            file << room.getLeftRoom()->getIndex() << endl;
        if (room.getRightRoom() == nullptr)
            file << -1 << endl;
        else
            file << room.getRightRoom()->getIndex() << endl;
        file << room.getName() << endl;
        file << room.getTag() << endl;
        file << room.getSandstormDuration() << endl;
        file << room.getChanceOfSandstorms() << endl;
        file << room.getChanceOfWaterSource() << endl;
        file << room.HasWaterSource() << endl;
        file << room.getChanceOfPoisonousWaterSource() << endl;
        file << room.getWSisPoisonous() << endl;
        file << room.HasSandstorm() << endl;
        file << room.getHungerIncreaseRate() << endl;
        file << room.getThirstIncreaseRate() << endl;
        file << room.getHungerChanges() << endl;
        file << room.getThirstChanges() << endl;
        file << room.IsExit() << endl;
        file << room.getIndex() << endl;
        file << room.getRoomCount() << endl;

        file << "#OBJECTS" << endl;
        for (Object *object : room.getObjects())
        {
            if (object->getTag() == "food" || object->getTag() == "drink" || object->getTag() == "equipment")
                file << "#ITEM" << endl;
            else if (object->getTag() == "monster")
                file << "#MONSTER" << endl;
            else if (object->getTag() == "npc")
                file << "#NPC" << endl;
            else if (object->getTag() == "livestock" || object->getTag() == "wildlife_forest" || object->getTag() == "wildlife_swamp")
                file << "#ANIMAL" << endl;

            file << object->getName() << endl;
            file << object->getTag() << endl;
            // ITEM
            if (object->getTag() == "food" || object->getTag() == "drink" || object->getTag() == "equipment")
            {
                Item *item = dynamic_cast<Item *>(object);
                file << item->getAttack() << endl;
                file << item->getDefense() << endl;
                file << item->getHealth() << endl;
                file << item->getNutritionalValue() << endl;
                file << item->getPoisonPotency() << endl;
                file << item->getPoisonDuration() << endl;
                file << item->getDetoxifyEffect() << endl;
                file << item->getPrice() << endl;
                file << item->IsPoisonous() << endl;
                file << item->IsDetoxifier() << endl;
            }
            // GAMECHARACTER
            else if (object->getTag() == "monster" || object->getTag() == "npc" || object->getTag() == "livestock" || object->getTag() == "wildlife_forest" || object->getTag() == "wildlife_swamp")
            {
                GameCharacter *gameCharacter = dynamic_cast<GameCharacter *>(object);
                file << gameCharacter->getMaxHealth() << endl;
                file << gameCharacter->getCurrentHealth() << endl;
                file << gameCharacter->getAttack() << endl;
                file << gameCharacter->getDefense() << endl;
                file << gameCharacter->getDodgeChance() << endl;
                file << gameCharacter->getGold() << endl;
                file << gameCharacter->getScript() << endl;
                // MONSTER
                if (object->getTag() == "monster")
                {
                    Monster *monster = dynamic_cast<Monster *>(object);
                    file << monster->IsBoss() << endl;
                    file << monster->getIsPoisonous() << endl;
                    file << monster->getPoisonDuration() << endl;
                    file << monster->getPoisonPotency() << endl;
                }
                // NPC
                else if (object->getTag() == "npc")
                {
                    NPC *npc = dynamic_cast<NPC *>(object);
                    file << "#COMMODITY" << endl;
                    for (Item item : npc->getCommodity())
                    {
                        file << "#ITEM" << endl;
                        file << item.getName() << endl;
                        file << item.getTag() << endl;
                        file << item.getAttack() << endl;
                        file << item.getDefense() << endl;
                        file << item.getHealth() << endl;
                        file << item.getNutritionalValue() << endl;
                        file << item.getPoisonPotency() << endl;
                        file << item.getPoisonDuration() << endl;
                        file << item.getDetoxifyEffect() << endl;
                        file << item.getPrice() << endl;
                        file << item.IsPoisonous() << endl;
                        file << item.IsDetoxifier() << endl;
                        file << "#endITEM" << endl;
                    }
                    file << "#endCOMMODITY" << endl;
                }
                // ANIMAL
                else if (object->getTag() == "livestock" || object->getTag() == "wildlife_forest" || object->getTag() == "wildlife_swamp")
                {
                    Animal *animal = dynamic_cast<Animal *>(object);
                    file << animal->getAttackChance() << endl;
                    file << animal->getWantToFight() << endl;
                }
            }
            if (object->getTag() == "food" || object->getTag() == "drink" || object->getTag() == "equipment")
                file << "#endITEM" << endl;
            else if (object->getTag() == "monster")
                file << "#endMONSTER" << endl;
            else if (object->getTag() == "npc")
                file << "#endNPC" << endl;
            else if (object->getTag() == "livestock" || object->getTag() == "wildlife_forest" || object->getTag() == "wildlife_swamp")
                file << "#endANIMAL" << endl;
        }
        file << "#endOBJECTS" << endl;
        file << "#endROOM" << endl;
    }
    file << "#endROOMS" << endl;
}

void Record::loadPlayer(Player *player, ifstream &file)
{
    string line;
    while (getline(file, line))
    {
        if (line == "#PLAYER")
        {
            getline(file, line);
            player->setName(line);
            getline(file, line);
            player->setTag(line);
            getline(file, line);
            player->setMaxHealth(stoi(line));
            getline(file, line);
            player->setCurrentHealth(stoi(line));
            getline(file, line);
            player->setAttack(stoi(line));
            getline(file, line);
            player->setDefense(stoi(line));
            getline(file, line);
            player->setDodgeChance(stoi(line));
            getline(file, line);
            player->setGold(stoi(line));
            getline(file, line);
            player->setScript(line);
            getline(file, line);
            player->setThirst(stoi(line));
            getline(file, line);
            player->setMaxThirst(stoi(line));
            getline(file, line);
            player->setHunger(stoi(line));
            getline(file, line);
            player->setMaxHunger(stoi(line));
            getline(file, line);
            player->setIsPoison(stoi(line));
            getline(file, line);
            player->setPoisonLevel(stoi(line));
            getline(file, line);
            player->setPoisonDuration(stoi(line));
            getline(file, line);
            player->setBuff(stoi(line));
            getline(file, line);
            player->setDebuff(stoi(line));
            getline(file, line);
            currentRoomIndex = stoi(line);
            getline(file, line);
            previousRoomIndex = stoi(line);
        }
        else if (line == "#INVENTORY")
        {
            while (getline(file, line))
            {
                if (line == "#ITEM")
                {
                    Item item;
                    getline(file, line);
                    item.setName(line);
                    getline(file, line);
                    item.setTag(line);
                    getline(file, line);
                    item.setAttack(stoi(line));
                    getline(file, line);
                    item.setDefense(stoi(line));
                    getline(file, line);
                    item.setHealth(stoi(line));
                    getline(file, line);
                    item.setNutritionalValue(stoi(line));
                    getline(file, line);
                    item.setPoisonPotency(stoi(line));
                    getline(file, line);
                    item.setPoisonDuration(stoi(line));
                    getline(file, line);
                    item.setDetoxifyEffect(stoi(line));
                    getline(file, line);
                    item.setPrice(stoi(line));
                    getline(file, line);
                    item.setIsPoisonous(stoi(line));
                    getline(file, line);
                    item.setIsDetoxifier(stoi(line));
                    player->addItem(item);
                }
                else if (line == "#endINVENTORY")
                {
                    break;
                }
            }
        }
        else if (line == "#EQUIPPEDITEMS")
        {
            while (getline(file, line))
            {
                if (line == "#ITEM")
                {
                    Item item;
                    getline(file, line);
                    item.setName(line);
                    getline(file, line);
                    item.setTag(line);
                    getline(file, line);
                    item.setAttack(stoi(line));
                    getline(file, line);
                    item.setDefense(stoi(line));
                    getline(file, line);
                    item.setHealth(stoi(line));
                    getline(file, line);
                    item.setNutritionalValue(stoi(line));
                    getline(file, line);
                    item.setPoisonPotency(stoi(line));
                    getline(file, line);
                    item.setPoisonDuration(stoi(line));
                    getline(file, line);
                    item.setDetoxifyEffect(stoi(line));
                    getline(file, line);
                    item.setPrice(stoi(line));
                    getline(file, line);
                    item.setIsPoisonous(stoi(line));
                    getline(file, line);
                    item.setIsDetoxifier(stoi(line));
                    player->addEquippedItem(item);
                }
                else if (line == "#endEQUIPPEDITEMS")
                {
                    break;
                }
            }
        }
        else if (line == "#endPLAYER")
        {
            break;
        }
    }
}

void Record::loadRooms(vector<Room> &rooms, ifstream &file)
{
    string line;
    while (getline(file, line))
    {
        if (line == "#ROOMS")
        {
            while (getline(file, line))
            {
                if (line == "#ROOM")
                {
                    Room room;
                    getline(file, line);
                    upRoomIndex.push_back(stoi(line));
                    getline(file, line);
                    downRoomIndex.push_back(stoi(line));
                    getline(file, line);
                    leftRoomIndex.push_back(stoi(line));
                    getline(file, line);
                    rightRoomIndex.push_back(stoi(line));
                    getline(file, line);
                    room.setName(line);
                    getline(file, line);
                    room.setTag(line);
                    getline(file, line);
                    room.setSandstormDuration(stoi(line));
                    getline(file, line);
                    room.setChanceOfSandstorms(stoi(line));
                    getline(file, line);
                    room.setChanceOfWaterSource(stoi(line));
                    getline(file, line);
                    room.setHasWaterSource(stoi(line));
                    getline(file, line);
                    room.setChanceOfPoisonousWaterSource(stoi(line));
                    getline(file, line);
                    room.setWSisPoisonous(stoi(line));
                    getline(file, line);
                    room.setHasSandstorm(stoi(line));
                    getline(file, line);
                    room.setHungerIncreaseRate(stoi(line));
                    getline(file, line);
                    room.setThirstIncreaseRate(stoi(line));
                    getline(file, line);
                    room.setHungerChanges(stoi(line));
                    getline(file, line);
                    room.setThirstChanges(stoi(line));
                    getline(file, line);
                    room.setIsExit(stoi(line));
                    getline(file, line);
                    room.setIndex(stoi(line));
                    getline(file, line);
                    room.setRoomCount(stoi(line));
                    while (getline(file, line))
                    {
                        if (line == "#OBJECTS")
                        {
                            while (getline(file, line))
                            {
                                if (line == "#ITEM")
                                {
                                    Item *item = new Item();
                                    getline(file, line);
                                    item->setName(line);
                                    getline(file, line);
                                    item->setTag(line);
                                    getline(file, line);
                                    item->setAttack(stoi(line));
                                    getline(file, line);
                                    item->setDefense(stoi(line));
                                    getline(file, line);
                                    item->setHealth(stoi(line));
                                    getline(file, line);
                                    item->setNutritionalValue(stoi(line));
                                    getline(file, line);
                                    item->setPoisonPotency(stoi(line));
                                    getline(file, line);
                                    item->setPoisonDuration(stoi(line));
                                    getline(file, line);
                                    item->setDetoxifyEffect(stoi(line));
                                    getline(file, line);
                                    item->setPrice(stoi(line));
                                    getline(file, line);
                                    item->setIsPoisonous(stoi(line));
                                    getline(file, line);
                                    item->setIsDetoxifier(stoi(line));
                                    room.addObject(static_cast<Object *>(item));
                                }
                                else if (line == "#MONSTER")
                                {
                                    Monster *monster = new Monster();
                                    getline(file, line);
                                    monster->setName(line);
                                    getline(file, line);
                                    monster->setTag(line);
                                    getline(file, line);
                                    monster->setMaxHealth(stoi(line));
                                    getline(file, line);
                                    monster->setCurrentHealth(stoi(line));
                                    getline(file, line);
                                    monster->setAttack(stoi(line));
                                    getline(file, line);
                                    monster->setDefense(stoi(line));
                                    getline(file, line);
                                    monster->setDodgeChance(stoi(line));
                                    getline(file, line);
                                    monster->setGold(stoi(line));
                                    getline(file, line);
                                    monster->setScript(line);
                                    getline(file, line);
                                    monster->setIsBoss(stoi(line));
                                    getline(file, line);
                                    monster->setIsPoisonous(stoi(line));
                                    getline(file, line);
                                    monster->setPoisonDuration(stoi(line));
                                    getline(file, line);
                                    monster->setPoisonPotency(stoi(line));
                                    room.addObject(static_cast<Object *>(monster));
                                }
                                else if (line == "#NPC")
                                {
                                    NPC *npc = new NPC(true);
                                    getline(file, line);
                                    npc->setName(line);
                                    getline(file, line);
                                    npc->setTag(line);
                                    getline(file, line);
                                    npc->setMaxHealth(stoi(line));
                                    getline(file, line);
                                    npc->setCurrentHealth(stoi(line));
                                    getline(file, line);
                                    npc->setAttack(stoi(line));
                                    getline(file, line);
                                    npc->setDefense(stoi(line));
                                    getline(file, line);
                                    npc->setDodgeChance(stoi(line));
                                    getline(file, line);
                                    npc->setGold(stoi(line));
                                    getline(file, line);
                                    npc->setScript(line);
                                    while (getline(file, line))
                                    {
                                        if (line == "#COMMODITY")
                                        {
                                            while (getline(file, line))
                                            {
                                                if (line == "#ITEM")
                                                {
                                                    Item item;
                                                    getline(file, line);
                                                    item.setName(line);
                                                    getline(file, line);
                                                    item.setTag(line);
                                                    getline(file, line);
                                                    item.setAttack(stoi(line));
                                                    getline(file, line);
                                                    item.setDefense(stoi(line));
                                                    getline(file, line);
                                                    item.setHealth(stoi(line));
                                                    getline(file, line);
                                                    item.setNutritionalValue(stoi(line));
                                                    getline(file, line);
                                                    item.setPoisonPotency(stoi(line));
                                                    getline(file, line);
                                                    item.setPoisonDuration(stoi(line));
                                                    getline(file, line);
                                                    item.setDetoxifyEffect(stoi(line));
                                                    getline(file, line);
                                                    item.setPrice(stoi(line));
                                                    getline(file, line);
                                                    item.setIsPoisonous(stoi(line));
                                                    getline(file, line);
                                                    item.setIsDetoxifier(stoi(line));
                                                    npc->addCommodity(item);
                                                }
                                                else if (line == "#endCOMMODITY")
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                        else if (line == "#endNPC")
                                        {
                                            break;
                                        }
                                    }
                                    room.addObject(static_cast<Object *>(npc));
                                }
                                else if (line == "#ANIMAL")
                                {
                                    Animal *animal = new Animal();
                                    getline(file, line);
                                    animal->setName(line);
                                    getline(file, line);
                                    animal->setTag(line);
                                    getline(file, line);
                                    animal->setMaxHealth(stoi(line));
                                    getline(file, line);
                                    animal->setCurrentHealth(stoi(line));
                                    getline(file, line);
                                    animal->setAttack(stoi(line));
                                    getline(file, line);
                                    animal->setDefense(stoi(line));
                                    getline(file, line);
                                    animal->setDodgeChance(stoi(line));
                                    getline(file, line);
                                    animal->setGold(stoi(line));
                                    getline(file, line);
                                    animal->setScript(line);
                                    getline(file, line);
                                    animal->setAttackChance(stoi(line));
                                    getline(file, line);
                                    animal->setWantToFight(stoi(line));
                                    room.addObject(static_cast<Object *>(animal));
                                }
                                else if (line == "#endOBJECTS")
                                {
                                    break;
                                }
                            }
                        }
                        else if (line == "#endROOM")
                        {
                            break;
                        }
                    }
                    rooms.push_back(room);
                }
                else if (line == "#endROOMS")
                {
                    break;
                }
            }
        }
    }
}
