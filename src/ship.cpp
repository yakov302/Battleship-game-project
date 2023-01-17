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
    m_points.set(x, y, ON_BORD);
}

void Ship::set_located(bool status)
{
    m_located = status;
}

void Ship::draw(sf::RenderWindow& a_window)const
{
    m_image.draw(a_window);
}; 


}//battle_ship namespace