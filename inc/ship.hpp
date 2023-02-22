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
    int length();

    int width();
    int right()const;
    int left()const;
    int top()const;
    int bottom()const;

    bool direction();
    bool is_the_ship_sank();
    bool is_in_range(int x, int y);

    void hit();
    void set_position(int x, int y);
    void draw(sf::RenderWindow& a_window)const;

private:
    int m_x;
    int m_y;
    int m_size;
    int m_hits;
    bool m_direction;
    Image m_image;
};


}//battle_ship namespace