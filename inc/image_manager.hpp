#pragma once

#include <vector>
#include <memory>
#include <unistd.h>

#include "image.hpp"

namespace battle_ship
{

#define X_Y_GUP 10
#define FIRE_X_GUP 14
#define FIRE_Y_GUP 11
#define NUM_OF_X 170
#define NUM_OF_FIRE 40

using ImagePtr = std::shared_ptr<Image>;

class ImageManager 
{
public:
    ImageManager();

    void set_x(int x, int y);
    void set_fire(int x, int y);
    void draw(sf::RenderWindow& window);

private:
    int m_x_index;
    int m_fire_index;
    std::vector<ImagePtr> m_x;
    std::vector<ImagePtr> m_fire;
};


}// battle_ship namespace
