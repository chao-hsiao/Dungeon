#include "Item.h"

const static string items_name[] = {"Sword", "Shield", "Armor", "Potion", "Scroll", "Ring", "Amulet", "Wand", "Staff", "Bow"};
const static string items_food_name[] = {"Apple", "Banana", "Orange", "Grapes", "Strawberry", "Pineapple", "Watermelon", "Cherry", "Peach", "Pear"};
const static string items_drink_name[] = {"Water", "Juice", "Milk", "Wine", "Beer", "Tea", "Coffee", "Soda", "Lemonade", "Cocktail"};

Item::Item() : health(rand() % 10 + 5), attack(rand() % 10 + 5), defense(rand() % 10 + 5), price(rand() % 20 + 10), nutritionalValue(0), poisonPotency(0), poisonDuration(0), isPoisonous(false), isDetoxifier(false), detoxifyEffect(0)
{
    int random = rand() % 3;
    if (random == 0)
        *this = Item("food");
    else if (random == 1)
        *this = Item("drink");
    else
        *this = Item("equipment");
}

Item::Item(string type) : health(rand() % 10 + 5), attack(rand() % 10 + 5), defense(rand() % 10 + 5), price(rand() % 20 + 10), nutritionalValue(0), poisonPotency(0), poisonDuration(0), isPoisonous(false), isDetoxifier(false), detoxifyEffect(0)
{
    setTag(type);

    if (type == "food" || type == "drink")
    {
        nutritionalValue = rand() % 30 + 15;      // nutritional value of the item with the food or drink type
        poisonPotency = rand() % 4 + 2;           // poison potency of the item
        isPoisonous = rand() % 2 ? true : false;  // poison status of the item
        poisonDuration = rand() % 4 + 2;          // poison duration of the item
        isDetoxifier = rand() % 2 ? true : false; // detoxifier status of the item
        detoxifyEffect = rand() % 4 + 2;          // detoxify effect of the item
        if (isPoisonous == true && isDetoxifier == true)
            rand() % 2 ? isPoisonous = false : isDetoxifier = false; // if the item is poisonous then it can't be a detoxifier and vice versa
    }

    if (type == "food")
    {
        setName(items_food_name[rand() % (sizeof(items_food_name) / sizeof(items_food_name[0]))]);
    }
    else if (type == "drink")
    {
        setName(items_drink_name[rand() % (sizeof(items_drink_name) / sizeof(items_drink_name[0]))]);
    }
    else if (type == "equipment")
    {
        setName(items_name[rand() % (sizeof(items_name) / sizeof(items_name[0]))]);
    }
}

// Pick up action
bool Item::triggerEvent(Object *object)
{
    Player *p = dynamic_cast<Player *>(object);
    if (p == nullptr)
    {
        return false;
    }
    // code that checks if the player already has the item, if so then he can't pick it up, else he does
    if (p->hasItem(getName()) && !(getTag() == "food" || getTag() == "drink"))
    {
        cout << "You already have " << getName() << "!" << endl
             << endl;
        return false;
    }
    cout << "You picked up " << getName() << "!" << endl
         << endl;
    p->addItem(*this);
    p->getCurrentRoom()->popObject(this);
    return true;
}

int Item::getHealth()
{
    return health;
}

int Item::getAttack()
{
    return attack;
}

int Item::getDefense()
{
    return defense;
}

void Item::setHealth(int health)
{
    this->health = health;
}

void Item::setAttack(int attack)
{
    this->attack = attack;
}

void Item::setDefense(int defense)
{
    this->defense = defense;
}

int Item::getPrice()
{
    return price;
}

void Item::setPrice(int price)
{
    this->price = price;
}

void Item::setNutritionalValue(int nutritionalValue)
{
    this->nutritionalValue = nutritionalValue;
}

bool Item::IsPoisonous()
{
    return isPoisonous;
}

int Item::getNutritionalValue()
{
    return nutritionalValue;
}

int Item::getPoisonPotency()
{
    return poisonPotency;
}

int Item::getPoisonDuration()
{
    return poisonDuration;
}

bool Item::IsDetoxifier()
{
    return isDetoxifier;
}

int Item::getDetoxifyEffect()
{
    return detoxifyEffect;
}

bool Item::operator==(const Item &other) const
{
    return this->getName() == other.getName();
}

void Item::setPoisonPotency(int poisonPotency)
{
    this->poisonPotency = poisonPotency;
}

void Item::setPoisonDuration(int poisonDuration)
{
    this->poisonDuration = poisonDuration;
}

void Item::setDetoxifyEffect(int detoxifyEffect)
{
    this->detoxifyEffect = detoxifyEffect;
}

void Item::setIsPoisonous(bool isPoisonous)
{
    this->isPoisonous = isPoisonous;
}

void Item::setIsDetoxifier(bool isDetoxifier)
{
    this->isDetoxifier = isDetoxifier;
}

Item::~Item() {}