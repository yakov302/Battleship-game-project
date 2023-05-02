#pragma once

#include <random>
#include <fstream>
#include <unordered_map>

#include "logic.hpp"

namespace battle_ship
{

#define NUM_OF_SHIPS 6

struct RivalShip
{
    int x;
    int y;
    int size;
    int hits;
    int index;
    bool direction;
};

using RivalShipsMap = std::unordered_map<int, RivalShip>;

class Rival
{
public:
    Rival();

    int x(int i);
    int y(int i);
    bool hit (int i);
    void empty_hit();
    void ship_sink(int index);
    int ship_size(int index);
    bool ship_direction(int index);
    void player_ship_hit(int x, int y);
    std::pair<int, int> play(Matrix& matrix);
    void place_the_ships_on_board(Matrix& matrix);

private:
    void locate_ship(int i, int distribution, int x, int y);

private:
    RivalShipsMap m_vertical;
    RivalShipsMap m_horizontal;
    RivalShipsMap m_locate_ships;

    Logic m_logic;
};


}//battle_ship namespace
