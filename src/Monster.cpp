#include "Monster.h"
#include "CommonFunc.h"

static string monster_names[] = {"Goblin", "Orc", "Troll", "Dragon", "Giant", "Golem", "Witch", "Vampire", "Werewolf", "Ghost"};
static string monster_scripts[] = {"I will kill.", "I will eat you.", "I will destroy you.", "I will crush you.", "I will burn you.", "I will smash you.", "I will curse you.", "I will suck your blood.", "I will bite you.", "I will haunt you."};
static string boss_name = "Boss";
static string boss_script = "I am the boss. I will tear you apart!";
static int monster_health[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
static int monster_attack[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
static int monster_defense[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static int monster_gold[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
static int monster_poison_potency[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static int monster_poison_duration[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

Monster::Monster() {}

Monster::Monster(bool isBoss) : isBoss(isBoss)
{
    setTag("monster");
    isPoisonous = rand() % 2 ? true : false;

    if (isBoss)
    {
        setName(boss_name);
        setScript(boss_script);
        setMaxHealth(100);                // boss's health
        setCurrentHealth(getMaxHealth()); // boss's health
        setAttack(50);                    // boss's attack
        setDefense(15);                   // boss's defense
        setGold(100);                     // boss's gold
        setDodgeChance(20);               // boss's dodge chance
        poisonPotency = 10;               // boss's poison potency
        poisonDuration = rand() % 5 + 2;  // boss's poison duration
    }
    else
    {
        setName(monster_names[rand() % sizeof(monster_names) / sizeof(monster_names[0])]);
        setScript(monster_scripts[rand() % sizeof(monster_scripts) / sizeof(monster_scripts[0])]);
        setMaxHealth(monster_health[rand() % sizeof(monster_health) / sizeof(int)]);
        setCurrentHealth(getMaxHealth());
        setAttack(monster_attack[rand() % sizeof(monster_attack) / sizeof(int)]);
        setDefense(monster_defense[rand() % sizeof(monster_defense) / sizeof(int)]);
        setDodgeChance(10);
        setGold(monster_gold[rand() % sizeof(monster_gold) / sizeof(int)]);
        poisonPotency = monster_poison_potency[rand() % sizeof(monster_poison_potency) / sizeof(int)];
        poisonDuration = monster_poison_duration[rand() % sizeof(monster_poison_duration) / sizeof(int)];
    }
}

bool Monster::triggerEvent(Object *object)
{
    Player *p = dynamic_cast<Player *>(object);
    if (p == nullptr)
    {
        return false;
    }
    showStatus();
    p->triggerEvent(p);
    cout << "You encountered " << getName() << ", a " << getTag() << "!" << endl
         << endl;
    cout << getName() << ": " << getScript() << endl
         << endl;
    while (true)
    {
        p->getCurrentRoom()->roomUpdateStatus();
        cout << "---------------- Attack or Run --------------" << endl;
        cout << "Choose an action" << endl;
        cout << " 1. Attack" << endl;
        cout << " 2. Run" << endl;
        cout << "---------------------------------------------" << endl
             << endl;

        switch (getUserChoice("Enter your choice", 1, 2))
        {
        case 1:
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
                cout << "You defeated " << getName() << "!" << endl;
                // p->increaseStates(0, 10, 0);
                if (!isBoss)
                    cout << "You get " << getGold() << " gold!" << endl
                         << endl;
                p->setGold(p->getGold() + getGold());
                p->getCurrentRoom()->popObject(this);
                return true;
            }

            cout << getName() << " attacks you!" << endl;
            if (rand() % 100 < p->getDodgeChance())
            {
                cout << "You dodge " << getName() << "'s attack!" << endl;
                cout << "Your health: " << p->getCurrentHealth() << endl
                     << endl;
            }
            else
            {
                cout << getName() << " deals " << p->takeDamage(getAttack()) << " damage to you!" << endl;
                cout << "Your health: " << p->getCurrentHealth() << endl
                     << endl;

                if (p->checkIsDead())
                {
                    p->getCurrentRoom()->setIgnoreUpdate();
                    p->setIgnoreCompletelyUpdate();
                    cout << "You are defeated by " << getName() << "!" << endl
                         << endl;
                    return false;
                }

                if (isPoisonous) // got hit and poisoned
                {
                    cout << getName() << " poisoned you!" << endl
                         << endl;
                    p->applyPoison(poisonPotency, poisonDuration);
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

            break;
        case 2:
            cout << "You run away from " << getName() << "!" << endl
                 << endl;
            p->changeRoom(p->getPreviousRoom());
            return false;
        default:
            break;
        }
    }
    return true;
}

void Monster::showStatus()
{
    isBoss ? cout << "--------------- Boss's Status ---------------" : cout << "------------- Monster's Status --------------";
    cout << endl;
    cout << "> Name: " << getName() << endl;
    cout << "> Health: " << getCurrentHealth() << endl;
    cout << "> Attack: " << getAttack() << endl;
    cout << "> Defense: " << getDefense() << endl;
    cout << "> Dodge Chance: " << getDodgeChance() << "%" << endl;
    cout << "> Gold: " << getGold() << endl;
    if (isPoisonous)
    {
        cout << "> Poisonous: Yes" << endl;
        cout << "> Poison Potency: " << poisonPotency << endl;
        cout << "> Poison Duration: " << poisonDuration << endl;
    }
    else
    {
        cout << "> Poisonous: No" << endl;
    }
    cout << "---------------------------------------------" << endl
         << endl;
}

bool Monster::IsBoss()
{
    return this->isBoss;
}

int Monster::getPoisonPotency()
{
    return poisonPotency;
}

int Monster::getPoisonDuration()
{
    return poisonDuration;
}

bool Monster::getIsPoisonous()
{
    return isPoisonous;
}

void Monster::setPoisonPotency(int potency)
{
    poisonPotency = potency;
}

void Monster::setPoisonDuration(int duration)
{
    poisonDuration = duration;
}

void Monster::setIsPoisonous(bool poisonous)
{
    isPoisonous = poisonous;
}

void Monster::setIsBoss(bool boss)
{
    isBoss = boss;
}

Monster::~Monster() {}