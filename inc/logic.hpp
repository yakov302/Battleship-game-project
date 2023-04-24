#pragma once

#include <utility>

#include "matrix.hpp"

namespace battle_ship
{

#define X true
#define Y false
#define SHIP 1
#define EMPTY 0
#define SHIP_HIT 2
#define EMPTY_HIT 3
#define HORIZONTAL true
#define VERTICAL false
#define FORWARD true
#define BACKWARD false
#define SHIPS_MAX_SIZE 5

class Logic
{
public:
    Logic();

    std::pair<int, int> play(Matrix& matrix);
    void ship_hit(int x, int y);
    void empty_hit();
    void ship_sink(int size);

private:
    std::pair<int, int> random_point(Matrix& matrix, int* ships_sizes);
    std::pair<int, int> pick_close_point(Matrix& matrix);

private:
    int m_ships_sizes[SHIPS_MAX_SIZE];
    std::pair<int, int> m_hit_point;

    int m_number_of_hits;
    bool m_hit_ship_direction;
    bool m_hit_play_direction;
};


}//battle_ship namespace
