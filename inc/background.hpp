#pragma once

#include "text.hpp"
#include "image.hpp"

namespace battle_ship
{

extern bool ships_location_phase;

class Background 
{
public:
    Background()
    : m_ackground("resources/images/background.jpg", 0, 0, 1)
    , m_grid_board_player("resources/images/grid_board.png", 140, 110, 1.3)
    , m_grid_board_rival("resources/images/grid_board.png", 810, 110, 1.3)
    , m_change_direction_button("resources/images/change_direction_button.png", 1785, 295, 0.17)
    , m_player("resources/fonts/arial.ttf", "you",  sf::Color(255, 228, 156), 50, 420, 55)
    , m_rival("resources/fonts/arial.ttf", "rival",  sf::Color(255, 228, 156), 50, 1085, 55)
    , m_message ("resources/fonts/arial.ttf", "",  sf::Color(255, 228, 156), 25, 1460, 600)
    , m_locate_message("resources/fonts/arial.ttf", "Place the ship on the board",  sf::Color(255, 228, 156), 25, 1460, 300)
    {

    };

    void draw(sf::RenderWindow& window)const
    {
        m_ackground.draw(window);
        m_grid_board_player.draw(window);
        m_grid_board_rival.draw(window);
        m_player.draw(window);
        m_rival.draw(window);
        m_message.draw(window);
        if(ships_location_phase)
        {
            m_change_direction_button.draw(window);
            m_locate_message.draw(window);
        }
    }; 

    bool is_change_direction_button_pressed(int x, int y)
    {
        return (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                m_change_direction_button.is_in_range(x, y));
    };

    void set_message(std::string message)
    {
        m_message.set_text(message);
        m_message.set_position(1645 - (message.size()*12)/2, 230);
    };
    
private:
    Image m_ackground;
    Image m_grid_board_player;
    Image m_grid_board_rival;
    Image m_change_direction_button;
    
    Text m_player;
    Text m_rival;
    Text m_message;
    Text m_locate_message;
};


}//battle_ship namespace