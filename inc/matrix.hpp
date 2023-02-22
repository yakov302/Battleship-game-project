#pragma once

#include <iostream>
#include <cassert>

namespace battle_ship
{
    
#define EMPTY 0
#define X_BASE 144
#define Y_BASE 120
#define SQUARE_SIZE 63
#define NUM_OF_COLUMNS 10
#define NUM_OF_POINTS 100
#define OUTSIDE_MATRIX_RANGE -1

struct Square
{
    int x;
    int y;
    int status;
    int ship_index;
};

class Matrix
{
public:
    Matrix();

    void set_status(int x, int y, int status);
    void set_square(int x, int y, int status, int ship_index);

    int give_x(int index);
    int give_y(int index);
    int give_index(int x, int y);
    int give_status(int x, int y);
    int give_ship_index(int x, int y);

    friend std::ostream& operator<<(std::ostream& a_os, Matrix const& matrix);

private:
    Square m_matrix[NUM_OF_POINTS];
};


}//battle_ship namespace