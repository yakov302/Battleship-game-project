#pragma once

#include <thread>
#include <iostream>
#include <unistd.h>
#include <utility>
#include <SFML/Graphics.hpp>

#include "background.hpp"
#include "ships_manager.hpp"
#include "image_manager.hpp"

namespace battle_ship
{

#define GAP 1
#define SHIP 1
#define EMPTY 0
#define SHIP_HIT 2
#define EMPTY_HIT 3

class Screen
{
public:
    Screen();
    ~Screen();

    void run();
    void stop();

private:
    void draw_locate();
    void draw_game();
    void check_mouse_locate();
    void check_mouse_game();
    void check_events();
    void locate_loop();
    void game_loop();

private:
    std::thread* m_thread;

    sf::Event m_event;
    sf::RenderWindow m_window;

    Matrix m_player_matrix;
    Background m_background;
    ShipManager m_ships_manager;
    ImageManager m_image_manager;
};


}//battle_ship namespace