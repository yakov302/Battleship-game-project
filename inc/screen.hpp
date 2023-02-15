#pragma once

#include <thread>
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "background.hpp"
#include "ships_manager.hpp"

namespace battle_ship
{

#define GAP 5
#define X_START_POINT 1550
#define Y_START_POINT 400

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

    Background m_background;
    ShipManager m_ships_manager;
};


}//battle_ship namespace