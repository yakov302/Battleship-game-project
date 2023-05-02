#pragma once

#include <thread>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "rival.hpp"
#include "sound.hpp"
#include "background.hpp"
#include "ships_manager.hpp"
#include "image_manager.hpp"

namespace battle_ship
{

#define GAP 1

class Screen
{
public:
    Screen();
    ~Screen();

    void run();
    void stop();

private:
    void one_time_draw();
    void draw_locate();
    void draw_game();
    void check_mouse_locate();
    void check_mouse_game();
    void check_events();
    void locate_loop();
    void game_loop();
    void start();
    void end();

private:
    std::thread* m_thread;

    sf::Event m_event;
    sf::RenderWindow m_window;

    Sound m_sound;
    Rival m_rival;
    Matrix m_player_matrix;
    Matrix m_rival_matrix;
    Background m_background;
    ShipManager m_ships_manager;
    ImageManager m_image_manager;
};


}//battle_ship namespace
