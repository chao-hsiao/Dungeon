#include "GameCharacter.h"

GameCharacter::GameCharacter() {}
GameCharacter::GameCharacter(string name, string script, string tag, int health, int attack, int defense, int gold) : Object(name, tag), currentHealth(health), attack(attack), defense(defense), gold(gold), script(script) {}

bool GameCharacter::checkIsDead()
{
    return currentHealth <= 0;
}

int GameCharacter::takeDamage(int damage)
{
    int damageTaken = damage - defense;
    if (damageTaken < 0)
    {
        damageTaken = 0;
    }
    if (currentHealth < damageTaken)
    {
        damageTaken = currentHealth;
        currentHealth = 0;
    }
    else
    {
        currentHealth -= damageTaken;
    }

    return damageTaken;
}

void GameCharacter::setMaxHealth(int maxHealth)
{
    this->maxHealth = maxHealth;
}

void GameCharacter::setCurrentHealth(int currentHealth)
{
    if (maxHealth < currentHealth)
        this->currentHealth = maxHealth;
    else if (currentHealth < 0)
        this->currentHealth = 0;
    else
        this->currentHealth = currentHealth;
}

void GameCharacter::setAttack(int attack)
{
    this->attack = attack;
}

void GameCharacter::setDefense(int defense)
{
    this->defense = defense;
}

void GameCharacter::setDodgeChance(int dodgeChance)
{
    this->dodgeChance = dodgeChance;
}

int GameCharacter::getMaxHealth()
{
    return maxHealth;
}

int GameCharacter::getCurrentHealth()
{
    return currentHealth;
}

int GameCharacter::getAttack()
{
    return attack;
}

int GameCharacter::getDefense()
{
    return defense;
}

int GameCharacter::getDodgeChance()
{
    return dodgeChance;
}

string GameCharacter::getScript()
{
    return script;
}

void GameCharacter::setGold(int gold)
{
    this->gold = gold;
}

int GameCharacter::getGold()
{
    return gold;
}

void GameCharacter::setScript(string script)
{
    this->script = script;
}

GameCharacter::~GameCharacter() {}