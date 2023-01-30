#pragma once

#include <thread>
#include <memory>
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "ship.hpp"
#include "background.hpp"

namespace battle_ship
{

#define X_START_POINT 0
#define Y_START_POINT 0
#define X_BASE 144
#define Y_BASE 120
#define SQUARE_SIZE 63
#define GAP 5


using ShipPtr = std::shared_ptr<Ship>;

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

private:
    sf::Event m_event;
    sf::RenderWindow m_window;

    std::thread* m_thread;
    Background m_background;

    //need to by deleted
    ShipPtr m_ship1;
    ShipPtr m_ship4;
    ShipPtr m_ship8;
    ShipPtr m_ship9;
    ShipPtr m_ship10;
    ShipPtr m_ship11;
};


}//battle_ship namespace