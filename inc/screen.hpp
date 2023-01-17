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
    std::shared_ptr<Ship> m_ship1;
    std::shared_ptr<Ship> m_ship2;
    std::shared_ptr<Ship> m_ship3;
    std::shared_ptr<Ship> m_ship4;
    std::shared_ptr<Ship> m_ship5;
    std::shared_ptr<Ship> m_ship6;
    std::shared_ptr<Ship> m_ship7;
    std::shared_ptr<Ship> m_ship8;
    std::shared_ptr<Ship> m_ship9;
    std::shared_ptr<Ship> m_ship10;
    std::shared_ptr<Ship> m_ship11;
    std::shared_ptr<Ship> m_ship12;
};


}//battle_ship namespace