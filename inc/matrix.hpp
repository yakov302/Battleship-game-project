#pragma once

#include <iostream>
#include <cassert>

namespace battle_ship
{

#define NUM_OF_COLUMNS 10
#define NUM_OF_POINTS 100

class Matrix
{
public:
    Matrix();

    int get(int x, int y);
    void set(int x, int y, int value);

    friend std::ostream& operator<<(std::ostream& a_os, Matrix const& matrix);

private:
    int m_matrix[NUM_OF_POINTS];
};


}//battle_ship namespace