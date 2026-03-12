#include "Player.hpp"
#include "Room.hpp"
#include "fogpi/io.hpp"
#include "Globals.hpp"
#include "Dice.hpp"
#include <vector>

void Player::Start(Vec2 _pos) {
    m_character = 'P';
    m_position = _pos;
}

void Player::Update() {
    char directionInput;

    do {
        directionInput = request_char("wasd and Enter to move");
    } while (directionInput != 'w' &&
             directionInput != 'a' &&
             directionInput != 's' &&
             directionInput != 'd');

    Vec2 direction(0,0);

    switch (directionInput)
    {
    case 'w':
        direction = {0, -1};
        break;
    case 'a':
        direction = {-1, 0};
        break;
    case 's':
        direction = {0, 1};
        break;
    case 'd':
        direction = {1, 0};
        break;
    }

    Vec2 tryPos = m_position + direction;

    // CHECK MONSTER FIRST
    Monster* monster = room->GetMonsterAt(tryPos);
    if (monster) {
        room->StartCombat(monster);
        return;
    }

    // KEY
    if (room->GetLocation(tryPos) == 'K') {
        m_keyCount++;
        room->ClearLocation(tryPos);
    }

    // MOVE
    if (room->GetLocation(tryPos) == ' ') {
        m_position = tryPos;
    }

    // DOOR
    if (room->GetLocation(tryPos) == 'D') {
        room->OpenDoor(tryPos);
    }

    //CHEST
    if (room->GetLocation(tryPos) == 'C')
    {
        int coinsFound = rand() % 6 + 3;
        int heal = rand() % 5 + 2;

        coins += coinsFound;
        health += heal;

        CurePoison();

        printf("You opened a chest!\n");
        printf("Found %d coins and healed %d health.\n", coinsFound, heal);
        printf("Poison cured!\n");

        room->ClearLocation(tryPos);
    }

    if (m_poisoned)
    {
        health -= m_poisonDamage;

        printf("Poison deals %d damage! Health: %d\n", m_poisonDamage, health);

        if (health <= 0)
        {
            printf("You died from poison!\n");
            exit(0);
        }
    }
}

void Player::PrintStats()
{
    printf("Health: %d\n", health);
    printf("Coins: %d\n", coins);
}

void Player::TakeDamage(int dmg)
{
    health -= dmg;

    printf("You take %d damage! Health now: %d\n", dmg, health);

    if (health <= 0)
    {
        printf("You died!\n");
    }
}

void Player::AddCoins(int amount)
{
    coins += amount;
}

void Player::ApplyPoison()
{
    m_poisoned = true;
    printf("You have been poisoned!\n");
}

void Player::CurePoison()
{
    if (m_poisoned)
    {
        m_poisoned = false;
        printf("You are cured of poison!\n");
    }
}

bool Player::IsDead() const
{
    return health <= 0;
}

std::vector<Die> Player::GetAttackDice() const
{
    return { Die{6}, Die{6} };
}