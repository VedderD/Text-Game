#pragma once
#include "Globals.hpp"
#include "Entity.hpp"
#include "Dice.hpp"
#include <vector>

extern int health;
extern int coins;

class Player : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
    void PrintStats();
    void TakeDamage(int dmg);
    void AddCoins(int amount);
    bool IsDead() const;
    void ApplyPoison();
    void CurePoison();
    std::vector<Die> GetAttackDice() const;
private:
    int m_keyCount = 0;
    bool m_poisoned = false;
    int m_poisonDamage = 2;
};