#pragma once

#include "matrix.hpp"
#include "image.hpp"

namespace battle_ship
{

#define HORIZONTAL true
#define VERTICAL false
#define ON_BORD true
#define NOT_ON_BORD false

class Ship
{
public:
    Ship(std::string image_path, int size, int x, int y, float scale, bool direction);

    int x();
    int y();
    int size();
    bool is_located();
    bool direction();
    void set_point(int x, int y);
    void set_located(bool status);
    void draw(sf::RenderWindow& a_window)const;

private:
    int m_x;
    int m_y;
    int m_size;
    bool m_located;
    bool m_direction;
    Image m_image;
    Matrix m_points;
};


}//battle_ship namespace