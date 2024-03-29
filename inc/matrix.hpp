#pragma once

#include <iostream>

namespace battle_ship
{
    
#define EMPTY 0
#define SQUARE_SIZE 63
#define X_RIVAL_BASE 814
#define Y_RIVAL_BASE 120
#define X_PLAYER_BASE 144
#define Y_PLAYER_BASE 120
#define NUM_OF_COLUMNS 10
#define NUM_OF_POINTS 100
#define OUTSIDE_MATRIX_RANGE -1

struct Square
{
    int x;
    int y;
    int status;
    int ship_index;
    bool direction;
};

class Matrix
{
public:
    Matrix(int x_base, int y_base);

    void set_status(int x, int y, int status);
    void set_square(int x, int y, int status, int ship_index, bool direction);

    int give_x(int x, int y);
    int give_y(int x, int y);
    int give_index(int x, int y);
    int give_status(int x, int y);
    int give_direction(int x, int y);
    int give_ship_index(int x, int y);

    friend std::ostream& operator<<(std::ostream& a_os, Matrix const& matrix);

private:
    int give_x(int index);
    int give_y(int index);

private:
    int m_x_base;
    int m_y_base;
    Square m_matrix[NUM_OF_POINTS];
};


}//battle_ship namespace
