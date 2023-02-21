#include "../inc/image_manager.hpp"
#include <iostream>

namespace battle_ship
{

namespace impl
{

void init_x(std::vector<ImagePtr>& vector)
{
    vector.reserve(170);
    for(int i = 0; i < 170; ++i)
        vector.emplace_back(ImagePtr(new Image("resources/images/x.png", 0, 0, 0.25)));
}

void init_fire(std::vector<ImagePtr>& vector)
{
    vector.reserve(40);
    for(int i = 0; i < 40; ++i)
        vector.emplace_back(ImagePtr(new Image("resources/images/fire.png", 0, 0, 0.08)));
}


}//impl namespace

ImageManager::ImageManager()
: m_x_index(0)
, m_fire_index(0)
{
    impl::init_x(m_x);
    impl::init_fire(m_fire);
}

void ImageManager::set_x(int x, int y)
{
    m_x[m_x_index].get()->set_position(x, y + X_Y_GUP);
    ++m_x_index;
}

void ImageManager::set_fire(int x, int y)
{
    m_fire[m_fire_index].get()->set_position(x + FIRE_X_GUP, y + FIRE_Y_GUP);
    ++m_fire_index;
}

void ImageManager::draw(sf::RenderWindow& window)
{
    for(int i = 0; i < m_x_index; ++i)
        m_x[i].get()->draw(window);
    
    for(int i = 0; i < m_fire_index; ++i)
        m_fire[i].get()->draw(window);
}


}// battle_ship namespace