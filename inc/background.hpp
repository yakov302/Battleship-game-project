#pragma once

#include "text.hpp"
#include "image.hpp"

namespace battle_ship
{

class Background 
{
public:
    Background()
    : m_ackground("resources/images/background.jpg", 0, 0, 1)
    , m_grid_board_player("resources/images/grid_board.png", 140, 110, 1.3)
    , m_grid_board_rival("resources/images/grid_board.png", 810, 110, 1.3)
    , m_player("resources/fonts/arial.ttf", "you",  sf::Color(255, 228, 156), 50, 420, 55)
    , m_rival("resources/fonts/arial.ttf", "rival",  sf::Color(255, 228, 156), 50, 1085, 55)
    {

    };

    void draw(sf::RenderWindow& window)const
    {
        m_ackground.draw(window);
        m_grid_board_player.draw(window);
        m_grid_board_rival.draw(window);
        m_player.draw(window);
        m_rival.draw(window);
    }; 
    
private:
    Image m_ackground;
    Image m_grid_board_player;
    Image m_grid_board_rival;
    Text m_player;
    Text m_rival;
};


}// poker battle_ship