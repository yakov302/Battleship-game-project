#pragma once

#include <random>
#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <unordered_map>

#include "matrix.hpp"

namespace battle_ship
{

#define SHIP 1
#define EMPTY_HIT 3
#define NUM_OF_SHIPS 6
#define HORIZONTAL true
#define VERTICAL false

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
    bool hit(int i);
    int ship_size(int index);
    bool ship_direction(int index);
    void place_the_ships_on_board(Matrix& matrix);

private:
    void locate_ship(int i, int distribution, int x, int y);

private:
    RivalShipsMap m_vertical;
    RivalShipsMap m_horizontal;
    RivalShipsMap m_locate_ships;
};


}//battle_ship namespace
