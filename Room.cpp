#include "Room.hpp"

#include "Player.hpp"
#include "Monster.hpp"
#include "Dice.hpp"
#include "Globals.hpp"

#include "fogpi/io.hpp"
#include <fstream>
#include <string>
#include <vector>

void Room::Load(std::string _path)
{
    m_map.clear();
    m_doors.clear();

    std::ifstream file;
    file.open(_path);

    if (!file.is_open())
    {
        printf("file not found at: %s \n", _path.c_str());
        exit(1);
    }

    std::string word;
    int number;

    while (file >> word)
    {
        if (word == "level")
        {
            if (file >> number)
            {
                printf("open level: %i\n", number);
            }
        }

        if (word == "next_level")
        {
            if (file >> word)
            {
                m_doors.push_back(Door());
                m_doors[m_doors.size() - 1].path = word;
            }
        }

        if (word == "map")
        {
            m_map.push_back(std::vector<char>());
            while(file >> word)
            {
                if (word == "-2")
                {
                    break;
                }

                if (word == "-1")
                {
                    m_map.push_back(std::vector<char>());
                    continue;
                }

                if (word == "0")
                    m_map[m_map.size() - 1].push_back(' ');
                else
                    m_map[m_map.size() - 1].push_back(word[0]);
                
            }
        }
    }

    int doorCount = 0;
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            if (m_map[y][x] == 'S')
            {
                if (m_player == nullptr)
                    m_player = new Player();
                
                m_player->Start(Vec2(x,y));
                m_map[y][x] = ' ';
            }

            if (m_map[y][x] == 'D' || m_map[y][x] == 'L')
            {
                if (m_doors.size() - 1 >= doorCount)
                {
                    m_doors[doorCount].pos.x = x;
                    m_doors[doorCount].pos.y = y;
                    doorCount++;
                }
            }

            if (m_map[y][x] == 'E')
            {
                Monster* monster = new Monster();
                monster->Start(Vec2(x,y));

                // Regular Monster
                monster->name = "Jackalope";
                m_monsters.push_back(monster);

                m_map[y][x] = ' ';
            }

            if (m_map[y][x] == 'P')
            {
                Monster* monster = new Monster();
                monster->Start(Vec2(x,y));
                monster->SetPoison(true);
                monster->name = "Cockatrice";
                m_monsters.push_back(monster);

                m_map[y][x] = ' ';
            }
        }
    }

    if (rand() % 2 == 0) // 20% chance
    {
        Vec2 pos;

        for (int i = 0; i < 50; i++) // prevent infinite loop
        {
            pos.x = rand() % m_map[0].size();
            pos.y = rand() % m_map.size();

            if (GetLocation(pos) == ' ')
            {
                m_map[pos.y][pos.x] = 'C';
                break;
            }
        }
    }
}

void Room::Update()
{
    Draw();
    if (m_player != nullptr)
    {
        m_player->room = this;
        m_player->Update();
    }
}

bool Room::AreMonstersAlive()
{
    for (Monster* m : m_monsters)
    {
        if (!m->IsDead())
            return true;
    }
    return false;
}

void Room::Draw()
{
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            printf("%c ", GetLocation(Vec2(x, y)));
        }
        printf("\n");
    }
}

char Room::GetLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return ' ';
    
    if (_pos.x >= m_map[_pos.y].size())
        return ' ';

    if (m_player != nullptr)
        if (m_player->GetPosition() == _pos)
            return m_player->Draw();

    for (Monster* m : m_monsters)
    {
        if (!m->IsDead() && m->GetPosition() == _pos)
            return m->Draw();
    }
    
    return m_map[_pos.y][_pos.x];
}

void Room::ClearLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return;
    
    if (_pos.x >= m_map[_pos.y].size())
        return;
    
    m_map[_pos.y][_pos.x] = ' ';
}

void Room::OpenDoor(Vec2 _pos)
{
    // check if monsters still alive
    if (AreMonstersAlive())
    {
        printf("The door is locked! Defeat all monsters first.\n");
        return;
    }

    for(int i = 0; i < m_doors.size(); i++)
    {
        if (m_doors[i].pos == _pos)
        {
            if (m_player != nullptr)
            {
                m_player->CurePoison();
                printf("You move to the next room.\n");
            }

            Load(m_doors[i].path.c_str());
        }
    }
}

Monster* Room::GetMonsterAt(Vec2 pos)
{
    for (Monster* m : m_monsters)
    {
        if (!m->IsDead() && m->GetPosition() == pos)
            return m;
    }

    return nullptr;
}

void Room::StartCombat(Monster* monster) {
    if (!monster) return;

    std::cout << "Combat started with a monster!\n";

    while (!monster->IsDead() && !m_player->IsDead()) {
        // Player attacks monster
        int damage = RollDice(m_player->GetAttackDice()).total;
        monster->TakeDamage(damage);
        std::cout << "You hit the monster for " << damage << " damage.\n";

        if (monster->IsDead()) break;

        // Monster attacks player
        int mDamage = RollDice(monster->GetAttackDice()).total;
        m_player->TakeDamage(mDamage);
        std::cout << monster->name << " hits you for " << mDamage << " damage.\n";

        if (monster->IsPoison())
        {
        if (rand() % 100 < 60)
            {
                m_player->ApplyPoison();
            }
        }

        int reward = rand() % 5 + 1; // 1-5 coins
        m_player->AddCoins(reward);

        printf("You gained %d coins!\n", reward);
    }

    // Combat ended, show result
    if (m_player->IsDead()) {
        std::cout << "You have died!\n";
        m_player->PrintStats();  // show final stats
        exit(0);                  // exit the game
    } 
    else
    {
        std::cout << "Monster defeated!\n";

        // small chance for coins
        int roll = random_int(1, 100);

        if (roll <= 25)  // 25% chance
        {
            int reward = random_int(1, 5);
            m_player->AddCoins(reward);
            std::cout << "You found " << reward << " coins!\n";
        }

        m_player->PrintStats();
    }
}