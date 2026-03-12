#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Dice.hpp"
#include "fogpi/Math.hpp"

class Monster {
public:
    std::string name = "Goblin";
    int health = 20;
    Vec2 m_position;

    bool m_poison = false;   // NEW: poison monster flag

    void Start(Vec2 pos) {
        m_position = pos;
    }

    Vec2 GetPosition() const {
        return m_position;
    }

    char Draw() const {
        if (m_poison)
            return 'B';   // poison monster symbol
        return 'M';
    }

    bool IsDead() const {
        return health <= 0;
    }

    void TakeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        std::cout << name << " takes " << dmg << " damage! Health now: " << health << "\n";
    }

    std::vector<Die> GetAttackDice() const {
        return { Die{6}, Die{6} };
    }

    // NEW functions
    void SetPoison(bool value) {
        m_poison = value;
    }

    bool IsPoison() const {
        return m_poison;
    }
};