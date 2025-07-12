#include "NPC.h"
#include "CommonFunc.h"

static const string npc_names[] = {"Alan", "Bob", "Charlie", "David", "Edward", "Frank", "George", "Henry", "Isaac", "Jack"};
static const string npc_scripts[] = {"Welcome to my shop.", "I have everything you need.", "I sell delicious food and drinks.", "Looking for something?", "I have the best items in town.", "I have the best prices.", "I have the best quality.", "I have the best service.", "I have the best selection.", "I have the best deals."};

NPC::NPC(bool) {}

NPC::NPC() : GameCharacter()
{
    int random_npc = rand() % sizeof(npc_names) / sizeof(string);
    int random_script = rand() % sizeof(npc_scripts) / sizeof(string);
    setTag("npc");
    setName(npc_names[random_npc]);
    string script = ("I am " + npc_names[random_npc] + ". " + npc_scripts[random_script]);
    setScript(script);
    setMaxHealth(100);
    setCurrentHealth(getMaxHealth());
    setAttack(10);
    setDefense(0);
    setGold(100);
    setDodgeChance(20);

    int item_num_npc = rand() % 4 + 1; // number of items in the NPC's shop
    for (int i = 0; i < item_num_npc; i++)
        commodity.push_back(Item());
}

void NPC::listCommodity()
{
    for (size_t i = 0; i < commodity.size(); i++)
    {
        cout << " " << i + 1 << ". " << commodity[i].getName() << ", " << commodity[i].getPrice() << " gold" << endl;
    }
    cout << " " << commodity.size() + 1 << ". Go Back" << endl;
}

bool NPC::triggerEvent(Object *object)
{
    unsigned int choice;
    Player *p = dynamic_cast<Player *>(object);
    if (p == nullptr)
    {
        return false;
    }
    cout << getName() << ": " << getScript() << endl
         << endl;
    p->getCurrentRoom()->roomUpdateStatus();

    cout << "-------------------- Shop -------------------" << endl;
    cout << "Choose an item to buy" << endl;
    if (commodity.size() == 0)
        cout << "Out of sell!" << endl;
    listCommodity();
    cout << "---------------------------------------------" << endl
         << endl;
    while (true)
    {
        cout << "   You have " << p->getGold() << " gold." << endl;
        choice = getUserChoice("What do you want to buy?", 1, commodity.size() + 1);

        if (choice == commodity.size() + 1)
        {
            cout << getName() << ": Have a nice day!" << endl
                 << endl;
            p->getCurrentRoom()->setIgnoreUpdate();
            p->setIgnoreCompletelyUpdate();
            return true;
        }
        if (p->getGold() < commodity[choice - 1].getPrice())
        {
            cout << getName() << ": You don't have enough money" << endl
                 << endl;
            p->getCurrentRoom()->setIgnoreUpdate();
            p->setIgnoreCompletelyUpdate();
            continue;
        }
        if (p->hasItem(commodity[choice - 1].getName()) && !(commodity[choice - 1].getTag() == "food" || commodity[choice - 1].getTag() == "drink"))
        {
            cout << getName() << ":You already have " << commodity[choice - 1].getName() << "!" << endl
                 << endl;
            p->getCurrentRoom()->setIgnoreUpdate();
            p->setIgnoreCompletelyUpdate();
            continue;
        }
        break;
    }
    cout << getName() << ": Thank you for your purchase!" << endl
         << endl;
    cout << "You bought " << commodity[choice - 1].getName() << " for " << commodity[choice - 1].getPrice() << " gold." << endl
         << endl;
    p->addItem(commodity[choice - 1]);
    p->setGold(p->getGold() - commodity[choice - 1].getPrice());
    commodity.erase(commodity.begin() + choice - 1);
    return true;
}

void NPC::setCommodity(vector<Item> commodity)
{
    this->commodity = commodity;
}

vector<Item> NPC::getCommodity()
{
    return commodity;
}

void NPC::showStatus()
{
    cout << "NPC's status:" << endl;
    cout << "> Name: " << getName() << endl;
    cout << "> Script: " << getScript() << endl;
    cout << "> Commodity: ";
    for (size_t i = 0; i < commodity.size(); i++)
    {
        cout << commodity[i].getName();
        if (i != commodity.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << endl;
}

void NPC::addCommodity(Item item)
{
    commodity.push_back(item);
}

NPC::~NPC() {}