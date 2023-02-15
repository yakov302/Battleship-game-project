#include "../inc/ship.hpp"

namespace battle_ship
{

Ship::Ship(std::string image_path, int size, int x = 0, int y = 0, float scale = 1, bool direction = HORIZONTAL)
: m_x(x)
, m_y(y)
, m_size(size)
, m_located(false)
, m_direction(false)
, m_image(image_path, x, y, scale)
{

}

int Ship::x()
{
    return m_x;
}

int Ship::y()
{
    return m_y;
}

int Ship::size()
{
    return m_size;
}

bool Ship::is_located()
{
    return m_located;
}

bool Ship::direction()
{
    return m_direction;
}

void Ship::set_point(int x, int y)
{
    m_points.set_status(x, y, ON_BORD);
}

void Ship::set_located(bool status)
{
    m_located = status;
}

void Ship::draw(sf::RenderWindow& a_window)const
{
    m_image.draw(a_window);
}; 

bool Ship::is_in_range(int x, int y)
{
    return m_image.is_in_range(x, y);
}

void Ship::set_position(int x, int y)
{
    m_image.set_position(x, y);
}

int Ship::length()
{
    return m_image.right() - m_image.left();
}

int Ship::width()
{
    return m_image.bottom() - m_image.top();
}

int Ship::right()const
{
    return m_image.right();
}

int Ship::left()const
{
    return m_image.left();
}

int Ship::top()const
{
   return m_image.top();
}

int Ship::bottom()const
{
    return m_image.bottom();
}

}//battle_ship namespace