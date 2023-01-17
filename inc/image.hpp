#pragma once

#include "shape.hpp"

namespace battle_ship
{

class Image : public Shape
{
public:
    Image(std::string image_path, int x = 0, int y = 0, float scale = 1)
    {
        m_texture.loadFromFile(image_path);
        m_shape.setTexture(m_texture);
        m_shape.scale(scale, scale);
        m_shape.setPosition(x, y);
    };

    bool is_in_range(int x, int y)
    {
        if( x <= this->right()  &&
            x >= this->left()   &&
            y <= this->bottom() &&
            y >= this->top()    
        )return true;

        return false;
    };

    void set_position(int x, int y)
    {
        m_shape.setPosition(x, y);
    }

    void set_scale(float scale)
    {
        m_shape.scale(scale, scale);
    }

    void draw(sf::RenderWindow& window)const
    {
        window.draw(m_shape);
    }; 
};


}// poker battle_ship