#pragma once

#include <vector>
#include <string>
#include<iostream>
#include "Door.hpp"
#include "Monster.hpp"
#include "fogpi/Math.hpp"

class Entity;
class Player;

class Room {
public:
    void Load(std::string _path);
    void Draw();
    void Update();
    bool AreMonstersAlive();
    char GetLocation(Vec2 _pos);
    void ClearLocation(Vec2 _pos);
    void OpenDoor(Vec2 _pos);
    void StartCombat(Monster* monster);
    Monster* GetMonsterAt(Vec2 pos);
private:
    std::vector<Entity*> m_entities;
    Player* m_player = nullptr;
    std::vector<Monster*> m_monsters;
    std::vector<std::vector<char>> m_map;
    std::vector<Door> m_doors;
};