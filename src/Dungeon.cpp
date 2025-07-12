#include "Dungeon.h"
#include "CommonFunc.h"
// #include <ctime>
// #include <cstdlib>
#include <cmath>

Dungeon::Dungeon() : isQuit(false), isEscape(false) {}

void Dungeon::createPlayer(int maxHealth, int attack, int defense, int gold)
{
    string name;
    cout << ">> Enter your name: ";
    cin >> name;
    cout << endl;
    string script = "I am " + name + ". Sosi moy chlen!";
    // Player(string name, string script, int health, int attack, int defense, int gold, )
    player = Player(name, script, maxHealth, attack, defense, gold);
    cout << "Hey " << player.getName() << "!" << endl;
    cout << "You have been given " << player.getGold() << " gold to start with." << endl
         << endl;
    // int choice;
    cout << "-------------------- Maps -------------------" << endl;
    cout << " 1. Map I" << endl;
    cout << " 2. Map II" << endl;
    cout << " 3. Map III"
         << "\t(This feature is not available yet)" << endl;
    cout << "---------------------------------------------" << endl
         << endl;

    while ((chosenMap = getUserChoice("Choose a map to play", 1, 3)))
    {
        if (chosenMap == 1 || chosenMap == 2)
            break;
        cout << "This feature is not available yet." << endl
             << endl;
    }
    handleEvent(&player);
}

void Dungeon::createMap()
{
    // srand(time(NULL));
    int roomNum = rand() % 20 + 5;
    int monster_num, npc_num, npc_animals_num, item_num;

    string roomSys;
    rooms = vector<Room>(roomNum);

    cout << "----------------- Room System ---------------" << endl;
    cout << " 1. Desert" << endl;
    cout << " 2. Forest" << endl;
    cout << " 3. Swamp" << endl;
    cout << " 4. Norm" << endl;
    cout << "---------------------------------------------" << endl
         << endl;
    switch (getUserChoice("Select a room system", 1, 4))
    {
    case 1:
        roomSys = "Desert";
        break;
    case 2:
        roomSys = "Forest";
        break;
    case 3:
        roomSys = "Swamp";
        break;
    default:
        roomSys = "Norm";
        break;
    }

    // Player's starting room
    rooms[0] = Room(false, vector<Object *>(), "Norm");

    // Exit room with a boss
    rooms[roomNum - 1] = Room(true, {new Monster(true)}, roomSys);

    // Generate random rooms
    for (int i = 1; i < roomNum - 1; i++)
    {
        monster_num = rand() % 2;     // number of monsters in the room
        npc_num = rand() % 3;         // number of NPCs in the room
        npc_animals_num = rand() % 3; // number of NPC's livestocks in the room
        item_num = rand() % 3;        // number of items in the room

        vector<Object *> objects; // objects in the room

        if (i != 1)
        {
            // Generate random monsters in the room
            for (int i = 0; i < monster_num; i++)
                objects.push_back(new Monster(false));
        }

        // Generate random NPCs in the room
        for (int i = 0; i < npc_num; i++)
            objects.push_back(new NPC()); // objects(NPCs) in the room

        // Generate random items in the room
        for (int i = 0; i < item_num; i++)
            objects.push_back(new Item());

        // Generate random NPC's livestocks or wildlifes in the room
        for (int i = 0; i < npc_animals_num; i++)
        {
            // objects(NPC's animals) in the room
            if ("Forest" == roomSys)
                objects.push_back(new Animal("wildlife_forest"));
            else if ("Swamp" == roomSys)
                objects.push_back(new Animal("wildlife_swamp"));
            else if ("Norm" == roomSys)
                objects.push_back(new Animal("livestock"));
        }

        // Assign those upper objects to the room and set the room system type
        rooms[i] = Room(false, objects, roomSys);
    }

    // set the current room of the player to the first room
    player.setCurrentRoom(&rooms[0]);

    // setting up the rooms in a linier way
    if (chosenMap == 1)
    {
        for (int i = 0; i < roomNum - 1; i++)
        {
            int random = rand() % 4;
            switch (random)
            {
            case 0:
                if (rooms[i].getUpRoom() != nullptr)
                    i--;
                else
                    rooms[i].setUpRoom(&rooms[i + 1]);
                break;
            case 1:
                if (rooms[i].getRightRoom() != nullptr)
                    i--;
                else
                    rooms[i].setRightRoom(&rooms[i + 1]);
                break;
            case 2:
                if (rooms[i].getDownRoom() != nullptr)
                    i--;
                else
                    rooms[i].setDownRoom(&rooms[i + 1]);
                break;
            case 3:
                if (rooms[i].getLeftRoom() != nullptr)
                    i--;
                else
                    rooms[i].setLeftRoom(&rooms[i + 1]);
                break;
            default:
                break;
            };
        }
    }

    // setting up the rooms in a 2D grid
    if (chosenMap == 2)
    {
        for (int i = 0; i < roomNum - 1; i++)
        {
            int random = rand() % 4;
            switch (random)
            {
            case 0:
                if (rooms[i].getUpRoom() != nullptr)
                    i--;
                else
                    rooms[i].setUpRoom(&rooms[i + 1]);
                break;
            case 1:
                if (rooms[i].getRightRoom() != nullptr)
                    i--;
                else
                    rooms[i].setRightRoom(&rooms[i + 1]);
                break;
            case 2:
                if (rooms[i].getDownRoom() != nullptr)
                    i--;
                else
                    rooms[i].setDownRoom(&rooms[i + 1]);
                break;
            case 3:
                if (rooms[i].getLeftRoom() != nullptr)
                    i--;
                else
                    rooms[i].setLeftRoom(&rooms[i + 1]);
                break;
            default:
                break;
            };
        }

        unsigned int randNum = rand() % (roomNum / 3) + (roomNum / 3);
        for (size_t i = 0; i < randNum; i++)
        {
            while (true)
            {
                int rand1 = rand() % (roomNum - 3) + 2;
                int rand2 = rand() % (roomNum - 3) + 2;
                int randd = rand() % 4;

                if (randd == 1 && rand1 != rand2 && rooms[rand1].getUpRoom() == nullptr && rooms[rand2].getDownRoom() == nullptr)
                    rooms[rand1].setUpRoom(&rooms[rand2]);
                else if (randd == 2 && rand1 != rand2 && rooms[rand1].getRightRoom() == nullptr && rooms[rand2].getLeftRoom() == nullptr)
                    rooms[rand1].setRightRoom(&rooms[rand2]);
                else if (randd == 3 && rand1 != rand2 && rooms[rand1].getDownRoom() == nullptr && rooms[rand2].getUpRoom() == nullptr)
                    rooms[rand1].setDownRoom(&rooms[rand2]);
                else if (randd == 4 && rand1 != rand2 && rooms[rand1].getLeftRoom() == nullptr && rooms[rand2].getRightRoom() == nullptr)
                    rooms[rand1].setLeftRoom(&rooms[rand2]);
                else
                    continue;
                break;
            }
        }
    }

    if (chosenMap == 3)
    {
    }
}

void Dungeon::handleMovement()
{
    player.getCurrentRoom()->triggerEvent(&player);
}

void Dungeon::handleEvent(Object *object)
{
    object->triggerEvent(&player);
}

void Dungeon::startGame()
{
    int health = 200;
    int attack = 10;
    int defense = 0;
    int gold = 100;

    cout << endl
         << "------------- Welcome to Dungeon! -----------" << endl;
    cout << "      _                                    \n"
         << "   __| |_   _ _ __   __ _  ___ _   _ _ __  \n"
         << "  / _` | | | | '_ \\ / _` |/ _ \\ | | | '_ \\ \n"
         << " | (_| | |_| | | | | (_| |  __/ |_| | | | |\n"
         << "  \\__,_|\\__,_|_| |_|\\__, |\\___|\\__,_|_| |_|\n"
         << "                    |___/                  \n"
         << endl;
    cout << "In this game, you will explore a dungeon with\nmultiple rooms." << endl;

    cout << "------------------ Main Menu ----------------" << endl;
    cout << " 1. Start New Game" << endl;
    cout << " 2. Load Game" << endl;
    cout << " 3. Exit" << endl;
    cout << "---------------------------------------------" << endl
         << endl;

    switch (getUserChoice("Select an option", 1, 3))
    {
    case 1:
    {
        cout << "Starting a new game..." << endl
             << endl;
        createPlayer(health, attack, defense, gold);
        createMap();
        break;
    }
    case 2:
        cout << "Loading game..." << endl;
        record.loadFromFile(&player, rooms);
        if (player.getCurrentRoom() == nullptr)
        {
            cout << "Starting a new game..." << endl
                 << endl;
            createPlayer(health, attack, defense, gold);
            createMap();
        }
        else
        {
            cout << "Game loaded successfully!" << endl
                 << endl;
        }
        cout << "You are now in " << player.getCurrentRoom()->getName() << endl
             << endl;
        handleEvent(&player);
        break;
    case 3:
        isQuit = true;
        break;
    }
}

void Dungeon::chooseAction(vector<Object *> objects)
{
    // srand(time(NULL));
    string obj;
    unsigned int choice;
    int minNumOfOptions = 6;

    obj = "";
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getTag() == "monster")
        {
            handleEvent(objects[i]);
            return;
        }
        if (objects[i]->getTag() == "npc")
        {
            obj += (" " + to_string(i + minNumOfOptions) + ". Interact with " + objects[i]->getName() + ", a " + objects[i]->getTag() + "\n");
        }
        if (objects[i]->getTag() == "livestock" || objects[i]->getTag() == "wildlife_forest" || objects[i]->getTag() == "wildlife_swamp")
        {
            if (dynamic_cast<Animal *>(objects[i])->getWantToFight())
            {
                handleEvent(objects[i]);
                return;
            }
            else
            {
                obj += (" " + to_string(i + minNumOfOptions) + ". Interact with " + objects[i]->getName() + ", an " + objects[i]->getTag() + "\n");
            }
        }
        if (objects[i]->getTag() == "food" || objects[i]->getTag() == "drink" || objects[i]->getTag() == "equipment")
        {
            obj += (" " + to_string(i + minNumOfOptions) + ". Pick up " + objects[i]->getName() + ", a/an " + objects[i]->getTag() + "\n");
        }
    }
    cout << "------------------- Actions -----------------" << endl;
    cout << "General Actions:" << endl;
    cout << " 1. Move" << endl;
    cout << " 2. Check My Status" << endl;
    cout << " 3. Equip an Item" << endl;
    cout << " 4. Unequip an Item" << endl;
    cout << " 5. Use an Item" << endl;

    if (obj != "")
        cout << endl
             << "Interacte with Objects:" << endl;
    cout << obj;

    if (player.getCurrentRoom()->HasWaterSource() && !player.getCurrentRoom()->IsExit())
    {
        cout << endl
             << "You found " << player.getCurrentRoom()->getWaterSourceName() << "!" << endl;
        cout << " " << (minNumOfOptions + objects.size()) << ". Restore thirst" << endl;
    }

    if (player.getCurrentRoom()->IsExit() && player.getCurrentRoom()->getObjects().size() == 0)
    {
        cout << endl
             << "You found the exit!" << endl;
        cout << " " << (minNumOfOptions + objects.size()) << ". Exit the Dungeon" << endl;
    }

    cout << endl
         << "Game Options:" << endl;
    cout << " " << (minNumOfOptions + objects.size() + (player.getCurrentRoom()->HasWaterSource() || player.getCurrentRoom()->IsExit())) << ". Save Game" << endl;
    cout << " " << (minNumOfOptions + objects.size() + (player.getCurrentRoom()->HasWaterSource() || player.getCurrentRoom()->IsExit()) + 1) << ". Exit Game" << endl;
    cout << "---------------------------------------------" << endl
         << endl;

    switch (choice = getUserChoice("Select an action", 1, minNumOfOptions + objects.size() + (player.getCurrentRoom()->HasWaterSource() || player.getCurrentRoom()->IsExit()) + 1))
    {
    case 1:
        handleMovement();
        break;
    case 2:
        player.getCurrentRoom()->setIgnoreUpdate();
        player.setIgnoreCompletelyUpdate();
        handleEvent(&player);
        break;
    case 3:
        player.equipItem();
        break;
    case 4:
        player.unequipItem();
        break;
    case 5:
        player.useItem();
        break;
    default:
        if (choice == minNumOfOptions + objects.size() + (player.getCurrentRoom()->HasWaterSource() || player.getCurrentRoom()->IsExit()) + 1)
        {
            cout << "------------------ Exit Game ----------------" << endl;
            cout << "Are you sure you want to exit the game?" << endl;
            cout << " 1. Yes" << endl;
            cout << " 2. No" << endl;
            cout << "---------------------------------------------" << endl
                 << endl;
            if (getUserChoice("Select", 1, 2) == 1)
                isQuit = true;
            player.getCurrentRoom()->setIgnoreUpdate();
            player.setIgnoreCompletelyUpdate();
        }
        else if (choice == minNumOfOptions + objects.size() + (player.getCurrentRoom()->HasWaterSource() || player.getCurrentRoom()->IsExit()))
        {
            player.getCurrentRoom()->setIgnoreUpdate();
            player.setIgnoreCompletelyUpdate();
            record.saveToFile(&player, rooms);
        }
        else if (player.getCurrentRoom()->HasWaterSource() && choice == minNumOfOptions + objects.size())
        {
            player.restoreThirst();
            if (rand() % 100 < player.getCurrentRoom()->getChanceOfPoisonousWaterSource())
            {
                cout << "You drank the water and got poisoned!" << endl
                     << endl;
                player.applyPoison(rand() % 4 + 2, rand() % 5 + 2);
            }
            player.setIgnoreUpdate();
        }
        else if (player.getCurrentRoom()->IsExit() && player.getCurrentRoom()->getObjects().size() == 0 && choice == minNumOfOptions + objects.size())
        {
            player.getCurrentRoom()->setIgnoreUpdate();
            player.setIgnoreCompletelyUpdate();
            isEscape = true;
        }
        else
            handleEvent(objects[choice - minNumOfOptions]);
        break;
    }
}

bool Dungeon::checkGameLogic()
{
    if (player.getCurrentRoom() == nullptr)
    {
        cout << "------------------ Goodbye! -----------------" << endl
             << endl;
        return false;
    }
    if (player.getCurrentRoom()->IsExit() && player.getCurrentRoom()->getObjects().size() == 0 && isEscape)
    {
        cout << "----------- Victory! You escaped! -----------" << endl
             << endl;
    }
    else if (player.checkIsDead())
    {
        cout << "----------------- Game Over! ----------------" << endl
             << endl;
    }
    else if (isQuit)
    {
        cout << "------------------ Goodbye! -----------------" << endl
             << endl;
    }
    else
        return true;

    return false;
}

void Dungeon::runDungeon()
{
    srand(time(NULL));
    startGame();
    while (checkGameLogic())
    {
        chooseAction(player.getCurrentRoom()->getObjects());
        player.getCurrentRoom()->roomUpdateStatus();
        player.updateStatus();
    }
}

Dungeon::~Dungeon()
{
    for (size_t i = 0; i < rooms.size(); i++)
    {
        for (size_t j = 0; j < rooms[i].getObjects().size(); j++)
        {
            delete rooms[i].getObjects()[j];
        }
    }
}
