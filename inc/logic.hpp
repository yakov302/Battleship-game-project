#pragma once

#include <utility>

#include "matrix.hpp"

namespace battle_ship
{

#define SHIP 1
#define EMPTY 0
#define SHIP_HIT 2
#define EMPTY_HIT 3
#define HORIZONTAL true
#define VERTICAL false
#define FORWARD true
#define BACKWARD false

class Logic
{
public:
    Logic();

    std::pair<int, int> play(Matrix& matrix);
    void ship_hit(int x, int y);
    void empty_hit();
    void ship_sink();

private:
    std::pair<int, int> random_point(Matrix& matrix);
    std::pair<int, int> pick_close_point(Matrix& matrix);

private:
    std::pair<int, int> m_hit_point;

    int m_number_of_hits;
    bool m_hit_ship_direction;
    bool m_hit_play_direction;
};


}//battle_ship namespace
