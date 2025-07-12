#include "Player.h"
#include "CommonFunc.h"
#include <algorithm>

int Player::roundCount = 0;

Player::Player() : currentRoom(nullptr), previousRoom(nullptr) {}

Player::Player(string name, string script, int health, int attack, int defense, int gold)
    : GameCharacter(name, script, "player", health, attack, defense, gold), thirst(100),  maxThirst(100), hunger(100), maxHunger(100), isPoison(false), poisonLevel(0), poisonDuration(0), buff(0), debuff(0), ignoreUpdate(false), ignoreCompletelyUpdate(false)
{
    setCurrentRoom(nullptr);
    setPreviousRoom(nullptr);
    setMaxHealth(health);
    setDodgeChance(20);
}

bool Player::triggerEvent(Object *)
{
    showStatus();
    return true;
}

void Player::addItem(Item item)
{
    inventory.push_back(item);
}

void Player::increaseStates(int health, int attack, int defense)
{
    setMaxHealth(getMaxHealth() + health);
    setAttack(getAttack() + attack);
    setDefense(getDefense() + defense);
}

void Player::changeRoom(Room *room)
{
    Room *temp = room;
    previousRoom = currentRoom;
    currentRoom = temp;
    cout << "You are now in Room " << currentRoom->getName() << endl
         << endl;
}

void Player::showStatus()
{
    cout << "---------------- Your Status ----------------" << endl;
    cout << "> Name: " << getName() << endl;
    cout << "> Health: " << getCurrentHealth() << "/" << getMaxHealth() << endl;
    cout << "> Attack: " << getEffectiveAttack() << endl;
    cout << "> Defense: " << getEffectiveDefense() << endl;
    cout << "> Dodge Chance: " << getDodgeChance() << "%" << endl;
    cout << "> Gold: " << getGold() << endl;
    cout << "> Hunger: " << hunger << "/" << maxHunger << endl;
    cout << "> Thirst: " << thirst << "/" << maxThirst << endl;
    cout << "> Poisoned: " << (isPoison ? "true" : "false") << endl;
    if (isPoison)
    {
        cout << "> Poison Level: " << poisonLevel << endl;
        cout << "> Poison Duration: " << poisonDuration << " turns left" << endl;
    }
    cout << "> Buff: " << buff << "\t(This feature is not available yet)" << endl;
    cout << "> Debuff: " << debuff << endl;
    if (!getInventory().empty())
    {
        cout << "> Items: ";
        for (size_t i = 0; i < getInventory().size(); i++)
        {
            cout << getInventory()[i].getName();
            if (i != getInventory().size() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
    if (!equippedItems.empty())
    {
        cout << "> Equipped Items: ";
        for (size_t i = 0; i < equippedItems.size(); i++)
        {
            cout << equippedItems[i].getName();
            if (i != equippedItems.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
    // cout << "> (All you want to add...)" << endl;
    cout << "---------------------------------------------" << endl
         << endl;
}

void Player::setCurrentRoom(Room *room)
{
    currentRoom = room;
}

void Player::setPreviousRoom(Room *room)
{
    previousRoom = room;
}

void Player::setInventory(vector<Item> inventory)
{
    this->inventory = inventory;
}

Room *Player::getCurrentRoom()
{
    return currentRoom;
}

Room *Player::getPreviousRoom()
{
    return previousRoom;
}

vector<Item> Player::getInventory()
{
    return inventory;
}

bool Player::hasItem(string name)
{
    for (size_t i = 0; i < inventory.size(); i++)
    {
        if (inventory[i].getName() == name)
        {
            return true;
        }
    }
    for (size_t i = 0; i < equippedItems.size(); i++)
    {
        if (equippedItems[i].getName() == name)
        {
            return true;
        }
    }
    return false;
}

bool Player::hasTypeInInventory(string type)
{
    if (type == "detoxifier")
        for (size_t i = 0; i < inventory.size(); i++)
            if (inventory[i].IsDetoxifier())
                return true;

    for (size_t i = 0; i < inventory.size(); i++)
        if (inventory[i].getTag() == type && !inventory[i].IsDetoxifier())
            return true;

    return false;
}

void Player::equipItem()
{
    int count = 0;
    vector<Item> tmp;
    cout << "---------------- Equipments -----------------" << endl;
    cout << "Choose an item to equip" << endl;
    if (!hasTypeInInventory("equipment"))
        cout << "You don't have any item to equip" << endl;
    else
    {
        for (size_t i = 0; i < inventory.size(); i++)
        {
            if (inventory[i].getTag() == "equipment")
            {
                cout << " " << ++count << ". " << inventory[i].getName() << endl;
                tmp.push_back(inventory[i]);
            }
        }
    }
    cout << " " << ++count << ". Go Back" << endl;
    cout << "---------------------------------------------" << endl;
    cout << endl;
    int choice = getUserChoice("Select an item to equip", 1, tmp.size() + 1);

    if (choice == count)
    {
        currentRoom->setIgnoreUpdate();
        setIgnoreCompletelyUpdate();
        return;
    }

    equipItem(tmp[choice - 1]);
}

void Player::unequipItem()
{
    cout << endl;
    cout << "---------------- Equipped Items ---------------" << endl;
    cout << "Choose an item to unequip" << endl;
    if (equippedItems.empty())
        cout << "You don't have any item to unequip" << endl;
    else
    {
        for (size_t i = 0; i < equippedItems.size(); i++)
        {
            cout << " " << i + 1 << ". " << equippedItems[i].getName() << endl;
        }
    }
    cout << " " << equippedItems.size() + 1 << ". Go Back" << endl;
    cout << "---------------------------------------------" << endl;
    cout << endl;
    unsigned int choice = getUserChoice("Select an item to unequip", 1, equippedItems.size() + 1);

    if (choice == equippedItems.size() + 1)
    {
        currentRoom->setIgnoreUpdate();
        setIgnoreCompletelyUpdate();
        return;
    }
    unequipItem(equippedItems[choice - 1]);
}

void Player::useItem()
{
    unsigned count = 0, choice;
    vector<string> types;
    vector<Item> tmp;
    string type;
    while (true)
    {
        count = 0;
        types.clear();
        tmp.clear();
        cout << "---------------- Item Actions ---------------" << endl;
        cout << "Choose what you want to do with item" << endl;
        // check  if there is any item to use
        if (!(hasTypeInInventory("food") || hasTypeInInventory("drink") || hasTypeInInventory("detoxifier")))
            cout << "You don't have any item to use" << endl;
        else
        {
            // list all action that player can do with item
            if (hasTypeInInventory("food"))
            {
                cout << " " << ++count << ". Eat" << endl;
                types.push_back("food");
            }
            if (hasTypeInInventory("drink"))
            {
                cout << " " << ++count << ". Drink" << endl;
                types.push_back("drink");
            }
            if (hasTypeInInventory("detoxifier"))
            {
                cout << " " << ++count << ". Detoxify" << endl;
                types.push_back("detoxifier");
            }
        }
        cout << " " << ++count << ". Go Back" << endl;
        cout << "---------------------------------------------" << endl;
        cout << endl;
        choice = getUserChoice("Select an action", 1, types.size() + 1);

        if (choice == count)
        {
            currentRoom->setIgnoreUpdate();
            setIgnoreCompletelyUpdate();
            return;
        }
        count = 0;

        // list all item that player choose from those action
        cout << "---------------- Item List ------------------" << endl;
        count = 0;
        type = types[choice - 1];
        if (type == "detoxifier")
            cout << "Choose something to use" << endl;
        else if (type == "food")
            cout << "Choose something to eat" << endl;
        else if (type == "drink")
            cout << "Choose something to drink" << endl;
        for (size_t i = 0; i < inventory.size(); i++)
        {
            if ((inventory[i].getTag() == type && !inventory[i].IsDetoxifier()) || (type == "detoxifier" && inventory[i].IsDetoxifier()))
            {
                cout << " " + to_string(++count) + ". ";
                cout << inventory[i].getName() << endl;
                tmp.push_back(inventory[i]);
            }
        }
        cout << " " << ++count << ". Go Back" << endl;
        cout << "---------------------------------------------" << endl;
        cout << endl;
        choice = getUserChoice("Select an item", 1, tmp.size() + 1);

        if (choice == count)
            continue;
        break;
    }

    if (hunger == maxHunger && type == "food")
    {
        cout << "You are full! You can't eat anymore!" << endl
             << endl;
        return;
    }
    if (thirst == maxThirst && type == "drink")
    {
        cout << "You are full! You can't drink anymore!" << endl
             << endl;
        return;
    }
    if (!isPoison && type == "detoxifier")
    {
        cout << "You are not poisoned! You can't detoxify!" << endl
             << endl;
        return;
    }

    if (type == "food")
    {
        eat(tmp[choice - 1]);
    }
    else if (type == "drink")
    {
        drink(tmp[choice - 1]);
    }
    else if (type == "detoxifier")
    {
        detoxify(tmp[choice - 1]);
    }
}

void Player::equipItem(Item item)
{
    equippedItems.push_back(item);
    inventory.erase(std::find(inventory.begin(), inventory.end(), item));
    cout << "You equip " << item.getName() << "!" << endl
         << endl;
    cout << "Attack: " << getEffectiveAttack() - item.getAttack() << " -> " << getEffectiveAttack() << endl;
    cout << "Defense: " << getEffectiveDefense() - item.getDefense() << " -> " << getEffectiveDefense() << endl
         << endl;
}

void Player::unequipItem(Item item)
{
    inventory.push_back(item);
    equippedItems.erase(std::find(equippedItems.begin(), equippedItems.end(), item));
    cout << "You unequip " << item.getName() << "!" << endl
         << endl;
    cout << "Attack: " << getEffectiveAttack() + item.getAttack() << " -> " << getEffectiveAttack() << endl;
    cout << "Defense: " << getEffectiveDefense() + item.getDefense() << " -> " << getEffectiveDefense() << endl
         << endl;
}

int Player::getEffectiveAttack()
{
    float debuffMultiplier = 1.0 - (0.1 * debuff); // 10% reduction per debuff level
    int effectiveAttack = getAttack() * debuffMultiplier;
    for (Item &item : equippedItems)
    {
        effectiveAttack += item.getAttack();
    }
    return effectiveAttack;
}

int Player::getEffectiveDefense()
{
    float debuffMultiplier = 1.0 - (0.1 * debuff); // 10% reduction per debuff level
    int effectiveDefense = getDefense() * debuffMultiplier;
    for (Item &item : equippedItems)
    {
        effectiveDefense += item.getDefense();
    }
    return effectiveDefense;
}

int Player::takeDamage(int damage)
{
    int damageTaken = damage - getEffectiveDefense();
    if (damageTaken < 0)
    {
        damageTaken = 0;
    }
    if (getCurrentHealth() < damageTaken)
    {
        damageTaken = getCurrentHealth();
        setCurrentHealth(0);
    }
    else
    {
        setCurrentHealth(getCurrentHealth() - damageTaken);
    }

    return damageTaken;
}

void Player::updateStatus()
{
    if (rand() % 100 < 2 && "Swamp" == currentRoom->getTag() && getCurrentHealth() != 0 && !ignoreUpdate)
    {
        cout << "You stucked in a swamp!" << endl;
        cout << "You died!" << endl
             << endl;
        setCurrentHealth(0);
        return;
    }

    int HealthChange = hunger * 0.1 + thirst * 0.1;
    int hungerChange = getCurrentRoom()->getHungerChanges();
    int thirstChange = getCurrentRoom()->getThirstChanges();

    if (isPoison && !ignoreCompletelyUpdate)
    {
        poisonDuration--;

        cout << "You are poisoned!" << endl;
        applyHealthChange(-poisonLevel); // Poison damage based on poison level
        cout << "Poison Duration: " << poisonDuration << " turns left." << endl
             << endl;
    }

    if (!ignoreUpdate)
        decreaseHunger(hungerChange);
    if (hunger <= 0 && !ignoreUpdate)
    {
        HealthChange = -10;

        cout << "Your hunger is critical!" << endl
             << endl;
        applyHealthChange(HealthChange); // Apply starvation damage
    }

    if (!ignoreUpdate)
        decreaseThirst(thirstChange);
    if (thirst <= 0 && !ignoreUpdate)
    {
        HealthChange = -10;
        cout << "Your thirst is critical!" << endl
             << endl;
        applyHealthChange(HealthChange); // Apply dehydration damage

        applyDebuff(2); // Apply a debuff due to dehydration
        cout << "Debuff increased by 2!" << endl
             << endl;
    }
    else if (thirst > 0 && debuff > 0 && !ignoreUpdate)
    {
        applyDebuff(-1); // Remove debuff if thirst is restored
        cout << "Debuff decreased by 1!" << endl
             << endl;
    }

    // Check if player is dead
    if (checkIsDead() && !ignoreUpdate)
    {
        if (thirst == 0)
            cout << "You died of thirst!" << endl;
        if (hunger == 0)
            cout << "You died of hunger!" << endl;
        if (poisonLevel > 0)
            cout << "You died of poison!" << endl;
        cout << endl;
        return;
    }
    // Reset poison status after duration ends
    if (poisonLevel <= 0 || poisonDuration <= 0)
    {
        poisonDuration = 0; // Reset poison duration after duration ends
        poisonLevel = 0;    // Reset poison level after duration ends
        isPoison = false;
    }

    // Regenerate health every 2 turns
    if (getCurrentHealth() != getMaxHealth() && hunger > 0 && thirst > 0 && roundCount % 2 == 0 && !ignoreCompletelyUpdate)
    {
        roundCount++;
        applyHealthChange(HealthChange);
    }

    ignoreUpdate = false;
    ignoreCompletelyUpdate = false;
}

void Player::eat(Item food)
{
    increaseHunger(food.getNutritionalValue());
    cout << "You eat " << food.getName() << ". Hunger restored " << hunger << "/" << maxHunger << "!" << endl
         << endl;
    setIgnoreUpdate();

    if (rand() % 100 < 10) // 15% chance to increase max health, attack, and defense from food
    {
        increaseStates(food.getHealth(), food.getAttack(), food.getDefense());
        cout << "You feel stronger after eating " << food.getName() << "!" << endl;
        cout << "Max health: " << getMaxHealth() - food.getHealth() << " -> " << getMaxHealth() << endl;
        cout << "Attack: " << getAttack() - food.getAttack() << " -> " << getAttack() << endl;
        cout << "Defense: " << getDefense() - food.getDefense() << " -> " << getDefense() << endl;
        cout << "Debuff: " << getDebuff() << " -> 0" << endl
             << endl;
        setDebuff(0);
    }

    if (food.IsPoisonous())
    {
        // Random chance to get poisoned from food
        if (rand() % 100 < 35)
        { // 35% chance to get poisoned
            applyPoison(food.getPoisonPotency(), food.getPoisonDuration());
            cout << "You are poisoned by " << food.getName() << "!" << endl;
            cout << "Your health: " << (getCurrentHealth() - food.getPoisonPotency() < 0 ? 0 : getCurrentHealth() - food.getPoisonPotency()) << endl
                 << endl;
        }
    }

    inventory.erase(std::find(inventory.begin(), inventory.end(), food));
}

void Player::drink(Item drink)
{
    increaseThirst(drink.getNutritionalValue());
    cout << "You drink " << drink.getName() << ". Thirst restored to " << thirst << "/" << maxThirst << "!" << endl
         << endl;
    setIgnoreUpdate();

    if (rand() % 100 < 10) // 15% chance to increase max health, attack, and defense from drink
    {
        increaseStates(drink.getHealth(), drink.getAttack(), drink.getDefense());
        cout << "You feel stronger after drinking " << drink.getName() << "!" << endl;
        cout << "Max health: " << getMaxHealth() - drink.getHealth() << " -> " << getMaxHealth() << endl;
        cout << "Attack: " << getAttack() - drink.getAttack() << " -> " << getAttack() << endl;
        cout << "Defense: " << getDefense() - drink.getDefense() << " -> " << getDefense() << endl;
        cout << "Debuff: " << getDebuff() << " -> 0" << endl
             << endl;
        setDebuff(0);
    }

    if (drink.IsPoisonous())
    {
        // Random chance to get poisoned from food
        if (rand() % 100 < 35)
        { // 35% chance to get poisoned
            applyPoison(drink.getPoisonPotency(), drink.getPoisonDuration());
            cout << "You are poisoned by " << drink.getName() << "!" << endl;
            cout << "Your health: " << (getCurrentHealth() - drink.getPoisonPotency() < 0 ? 0 : getCurrentHealth() - drink.getPoisonPotency()) << endl
                 << endl;
        }
    }

    inventory.erase(std::find(inventory.begin(), inventory.end(), drink));
}

void Player::detoxify(Item detoxifier)
{
    if (poisonLevel > 0)
    {
        setIgnoreUpdate();
        cout << "Using " << detoxifier.getName() << " to reduce poison." << endl;
        poisonLevel -= detoxifier.getDetoxifyEffect();

        if (detoxifier.getTag() == "drink")
            increaseThirst(detoxifier.getNutritionalValue());
        else if (detoxifier.getTag() == "food")
            increaseHunger(detoxifier.getNutritionalValue());

        applyHealthChange(detoxifier.getNutritionalValue() / 20);

        if (poisonLevel <= 0)
        {
            poisonLevel = 0;
            poisonDuration = 0;
            isPoison = false;
        }
        cout << "Poison level is now " << poisonLevel << "." << endl;
        cout << "Your health: " << (getCurrentHealth() - poisonLevel < 0 ? 0 : getCurrentHealth() - poisonLevel) << endl
             << endl;
        inventory.erase(std::find(inventory.begin(), inventory.end(), detoxifier));
    }
    else
    {
        cout << "No need to detoxify now." << endl
             << endl;
    }
}

void Player::applyPoison(int potency, int duration)
{
    poisonLevel = max(poisonLevel, potency);
    poisonDuration = max(poisonDuration, duration);
    isPoison = true;
}

void Player::increaseHunger(int amount)
{
    hunger += amount;
    if (hunger > maxHunger)
    {
        hunger = maxHunger;
    }
}

void Player::decreaseHunger(int amount)
{
    hunger -= amount;
    if (hunger < 0)
    {
        hunger = 0;
    }
}

void Player::increaseThirst(int amount)
{
    thirst += amount;
    if (thirst > maxThirst)
    {
        thirst = maxThirst;
    }
}

void Player::decreaseThirst(int amount)
{
    thirst -= amount;
    if (thirst < 0)
    {
        thirst = 0;
    }
}

void Player::restoreThirst()
{
    thirst = maxThirst;
    cout << "Thirst restored to " << thirst << "/" << maxThirst << "!" << endl
         << endl;
}

void Player::applyHealthChange(int change)
{
    if (change > 0)
    {
        int newHealth = std::max(0, std::min(getCurrentHealth() + change, getMaxHealth()));
        cout << "Heath regenerates to " << newHealth << "!" << endl
             << endl;
        setCurrentHealth(newHealth);
        return;
    }

    setCurrentHealth(getCurrentHealth() + change);
    cout << "You got " << -change << " damage!" << endl;
    cout << "Your health: " << getCurrentHealth() << endl
         << endl;
}

void Player::applyDebuff(int severity)
{
    debuff += severity;
}

void Player::applyBuff(int bonus)
{
    buff += bonus;
}

void Player::setIgnoreUpdate()
{
    ignoreUpdate = true;
}

void Player::setIgnoreCompletelyUpdate()
{
    ignoreCompletelyUpdate = true;
    ignoreUpdate = true;
}

vector<Item> Player::getequippedItems()
{
    return equippedItems;
}

void Player::addEquippedItem(Item item)
{
    equippedItems.push_back(item);
}

int Player::getThirst()
{
    return thirst;
}

int Player::getMaxThirst()
{
    return maxThirst;
}

int Player::getHunger()
{
    return hunger;
}

int Player::getMaxHunger()
{
    return maxHunger;
}

bool Player::IsPoison()
{
    return isPoison;
}

int Player::getPoisonLevel()
{
    return poisonLevel;
}

int Player::getPoisonDuration()
{
    return poisonDuration;
}

int Player::getBuff()
{
    return buff;
}

int Player::getDebuff()
{
    return debuff;
}

void Player::setThirst(int thirst)
{
    this->thirst = thirst;
}

void Player::setMaxThirst(int maxThirst)
{
    this->maxThirst = maxThirst;
}

void Player::setHunger(int hunger)
{
    this->hunger = hunger;
}

void Player::setMaxHunger(int maxHunger)
{
    this->maxHunger = maxHunger;
}

void Player::setIsPoison(bool isPoison)
{
    this->isPoison = isPoison;
}

void Player::setPoisonLevel(int poisonLevel)
{
    this->poisonLevel = poisonLevel;
}

void Player::setPoisonDuration(int poisonDuration)
{
    this->poisonDuration = poisonDuration;
}

void Player::setBuff(int buff)
{
    this->buff = buff;
}

void Player::setDebuff(int debuff)
{
    this->debuff = debuff;
}

Player::~Player() {}