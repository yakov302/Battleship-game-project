#pragma once

#include <thread>
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "ship.hpp"
#include "background.hpp"
#include "ships_manager.hpp"

namespace battle_ship
{

#define X_START_POINT 0
#define Y_START_POINT 0
#define X_BASE 144
#define Y_BASE 120
#define SQUARE_SIZE 63
#define GAP 5

class Screen
{
public:
    Screen();
    ~Screen();
    void stop();

    void run();
    void draw_all();
    void check_mouse();
    void check_events();
    void ships_location_phase_loop();


private:
    sf::Event m_event;
    sf::RenderWindow m_window;

    std::thread* m_thread;
    Background m_background;
    ShipManager m_ships_manager;
};


}//battle_ship namespace