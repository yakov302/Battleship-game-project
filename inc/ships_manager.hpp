#pragma once

#include <memory>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "ship.hpp"

namespace battle_ship
{

#define NUM_OF_SHIPS 6
#define X_START_POINT 1645
#define Y_START_POINT 360
#define SHIPS_IMAGES_FOLDER "resources/images/"

using ShipPtr = std::shared_ptr<Ship>;
using ShipsMap = std::unordered_map<int, ShipPtr>;

class ShipManager
{
public:
    ShipManager();

    int x(int i, bool direction);
    int y(int i, bool direction);
    int left(int i, bool direction);
    int right (int i, bool direction);
    int top(int i, bool direction); 
    int bottom(int i, bool direction);
    int width(int i, bool direction);
    int length (int i, bool direction);
    int size (int i, bool direction);

    void locate_ship(int i, bool direction);
    void draw_located_ships(sf::RenderWindow& window);
    void set_ship_position(int i, bool direction, int x, int y);
    void draw_ship(int i, bool direction, sf::RenderWindow& window);
    bool is_mouse_pressed_on_the_ship(int i, bool direction, int x, int y);

private:
    ShipsMap m_vertical;
    ShipsMap m_horizontal;
    ShipsMap m_locate_ships;
};



}//battle_ship namespace