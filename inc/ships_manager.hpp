#pragma once

#include <memory>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "ship.hpp"

namespace battle_ship
{

#define NUM_OF_SHIPS 6

using ShipPtr = std::shared_ptr<Ship>;
using ShipsMap = std::unordered_map<int, ShipPtr>;

class ShipManager
{
public:
    ShipManager();
    void set_ship_position(int i, bool direction, int x, int y);
    void print_ship(int i, bool direction, sf::RenderWindow& window);
    bool is_mouse_pressed_on_the_ship(int i, bool direction, int x, int y);

    int left(int i, bool direction);
    int right (int i, bool direction);
    int top(int i, bool direction); 
    int bottom(int i, bool direction);
    int width(int i, bool direction);
    int length (int , bool direction);

private:
    ShipsMap m_vertical;
    ShipsMap m_horizontal;
};



}//battle_ship namespace