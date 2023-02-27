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
#define NUM_OF_SHIPS 6
#define HORIZONTAL true
#define VERTICAL false

struct RivalShip
{
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

    void hit(int i);
    void place_the_ships_on_board(Matrix& matrix);

private:
    RivalShipsMap m_vertical;
    RivalShipsMap m_horizontal;
    RivalShipsMap m_locate_ships;
};


}//battle_ship namespace
