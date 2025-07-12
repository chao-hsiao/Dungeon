#include "Animal.h"
#include "CommonFunc.h"

static const string npc_livestocks[][2] = {
    {"Chicken", "Cluck! Cluck!"},
    {"Cow", "Moo! Moo!"},
    {"Duck", "Quack! Quack!"},
    {"Goat", "Baa! Baa!"},
    {"Horse", "Neigh! Neigh!"},
    {"Pig", "Oink! Oink!"},
    {"Sheep", "Baa! Baa!"},
    {"Turkey", "Gobble! Gobble!"},
    {"Rabbit", "Squeak! Squeak!"},
    {"Dog", "Woof! Woof!"}};

static const string npc_wildlifes_in_forest[][2] = {
    {"Bear", "Roar! Roar!"},
    {"Wolf", "Howl! Howl!"},
    {"Lion", "Roar! Roar!"},
    {"Tiger", "Roar! Roar!"},
    {"Panther", "Roar! Roar!"},
    {"Coyote", "Howl! Howl!"},
    {"Jaguar", "Roar! Roar!"},
    {"Leopard", "Roar! Roar!"},
    {"Cheetah", "Roar! Roar!"},
    {"Hyena", "Laugh! Laugh!"}};
static const string npc_wildlifes_in_swamp[][2] = {
    {"Crocodile", "Roar! Roar!"},
    {"Alligator", "Roar! Roar!"},
    {"Anaconda", "Hiss! Hiss!"},
    {"Python", "Hiss! Hiss!"},
    {"Boa", "Hiss! Hiss!"},
    {"Viper", "Hiss! Hiss!"},
    {"Cobra", "Hiss! Hiss!"},
    {"Rattlesnake", "Hiss! Hiss!"},
    {"Mamba", "Hiss! Hiss!"},
    {"Black Widow", "Hiss! Hiss!"}};

Animal::Animal() {}

Animal::Animal(string type) : GameCharacter()
{
    setMaxHealth(100);
    setCurrentHealth(getMaxHealth());
    setDefense(0);
    setGold(100);

    int num_rows;
    setTag(type);

    if (type == "livestock")
    {
        num_rows = sizeof(npc_livestocks) / sizeof(npc_livestocks[0]);
        setName(npc_livestocks[num_rows][0]);
        setScript(npc_livestocks[num_rows][1]);
        setAttack(3);
        attackChance = 20;
        setDodgeChance(30);
    }
    else if (type == "wildlife_forest")
    {
        num_rows = rand() % sizeof(npc_wildlifes_in_forest) / sizeof(npc_wildlifes_in_forest[0]);
        setName(npc_wildlifes_in_forest[num_rows][0]);
        setScript(npc_wildlifes_in_forest[num_rows][1]);
        setAttack(12);
        attackChance = 80;
        setDodgeChance(20);
        wantToFight = rand() % 100 < attackChance ? true : false;
    }
    else if (type == "wildlife_swamp")
    {
        num_rows = rand() % sizeof(npc_wildlifes_in_swamp) / sizeof(npc_wildlifes_in_swamp[0]);
        setName(npc_wildlifes_in_swamp[num_rows][0]);
        setScript(npc_wildlifes_in_swamp[num_rows][1]);
        setAttack(12);
        attackChance = 80;
        setDodgeChance(20);
        wantToFight = rand() % 100 < attackChance ? true : false;
    }
}

// the triger event enters a loop in the game where the player kills the Animal and gets its meat and popup the livestock from the room
bool Animal::triggerEvent(Object *object)
{
    Player *p = dynamic_cast<Player *>(object);
    if (p == nullptr)
    {
        return false;
    }

    showStatus();
    p->triggerEvent(p);
    if (wantToFight)
    {
        cout << "You encountered " << getName() << ", an " << getTag() << "!" << endl
             << endl;
        cout << getName() << ": " << getScript() << endl
             << endl;
    }

    while (true)
    {
        p->getCurrentRoom()->roomUpdateStatus();
        if (wantToFight)
        {
            cout << "---------------- Attack or Run --------------" << endl;
            cout << "Choose an action" << endl;
            cout << " 1. Attack" << endl;
            cout << " 2. Run" << endl;
            cout << "---------------------------------------------" << endl
                 << endl;

            if (getUserChoice("Enter your choice", 1, 2) == 2)
            {
                cout << "You run away from " << getName() << "!" << endl
                     << endl;
                if (getTag() == "wildlife_forest" || getTag() == "wildlife_swamp")
                    wantToFight = rand() % 100 < attackChance ? true : false;
                p->changeRoom(p->getPreviousRoom());
                return false;
            }
        }
        else
        {
            cout << "----------- To kill or not to kill? ---------" << endl;
            cout << "What do you want to do?" << endl;
            cout << "1. Kill it!" << endl;
            cout << "2. Spared " << getName() << "!" << endl;
            cout << "---------------------------------------------" << endl
                 << endl;
            if (getUserChoice("Enter your choice", 1, 2) == 2)
            {
                cout << "You have spared " << getName() << "." << endl
                     << endl;
                p->setIgnoreCompletelyUpdate();
                p->getCurrentRoom()->setIgnoreUpdate();
                return false;
            }
            else if (getTag() == "wildlife_forest" || getTag() == "wildlife_swamp")
                wantToFight = true;
        }

        cout << "You attack " << getName() << "!" << endl;
        if (rand() % 100 < getDodgeChance())
        {
            cout << getName() << " dodges your attack!" << endl;
        }
        else
        {
            cout << "You deal " << takeDamage(p->getEffectiveAttack()) << " damage to " << getName() << "!" << endl;
        }
        cout << getName() << "'s health: " << getCurrentHealth() << endl
             << endl;
        if (checkIsDead())
        {
            cout << "You have killed " << getName() << "." << endl;
            Item meat = Item("food");
            meat.setName(getName() + " Meat");
            meat.setIsDetoxifier(false);
            p->addItem(meat);
            cout << "You have obtained " << meat.getName() << "!" << endl
                 << endl;
            p->getCurrentRoom()->popObject(this);
            return true;
        }

        if (rand() % 100 < getAttackChance())
        {
            cout << getName() << " attacks you!" << endl;
            cout << getName() << " deals " << p->takeDamage(getAttackChance() * 0.15) << " damage to you!" << endl;
            cout << "Your health: " << p->getCurrentHealth() << endl
                 << endl;
            if (p->checkIsDead())
            {
                cout << "You have been defeated by " << getName() << "!" << endl
                     << endl;
                p->getCurrentRoom()->setIgnoreUpdate();
                p->setIgnoreCompletelyUpdate();
                return false;
            }
        }

        p->updateStatus(); // hunger sys
        if (p->checkIsDead())
        {
            p->getCurrentRoom()->setIgnoreUpdate();
            p->setIgnoreCompletelyUpdate();
            // cout << "You are defeated by " << getName() << "!" << endl;
            return false;
        }
    }
    return true;
}

void Animal::showStatus()
{
    cout << "------------------- Animal ------------------" << endl;
    cout << "> Name: " << getName() << endl;
    cout << "> Health: " << getCurrentHealth() << "/" << getMaxHealth() << endl;
    cout << "> Attack: " << getAttack() << endl;
    cout << "> AttackChance: " << getAttackChance() << "%" << endl;
    cout << "> DodgeChance: " << getDodgeChance() << "%" << endl;
    cout << "---------------------------------------------" << endl
         << endl;
}

int Animal::getAttackChance()
{
    return attackChance;
}

bool Animal::getWantToFight()
{
    return wantToFight;
}

void Animal::setAttackChance(int chance)
{
    attackChance = chance;
}

void Animal::setWantToFight(bool wantFight)
{
    wantToFight = wantFight;
}

Animal::~Animal() {}