#include "../inc/image_manager.hpp"

namespace battle_ship
{

namespace impl
{

void init_x(std::vector<ImagePtr>& vector)
{
    vector.reserve(NUM_OF_X);
    for(int i = 0; i < NUM_OF_X; ++i)
        vector.emplace_back(ImagePtr(new Image("resources/images/x.png", 0, 0, 0.25)));
}

void init_fire(std::vector<ImagePtr>& vector)
{
    vector.reserve(NUM_OF_FIRE);
    for(int i = 0; i < NUM_OF_FIRE; ++i)
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
