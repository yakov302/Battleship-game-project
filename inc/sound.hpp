#pragma once

#include <fstream>
#include <SFML/Audio.hpp>

namespace battle_ship
{

#define NUM_OF_SOUNDS 9

class Sound
{
public:
    Sound();

    void play_invalid();
    void play_anchor();
    void play_button();
    void play_empty_hit();
    void play_hit();
    void play_sinking();
    void play_win();
    void play_fail();
    void play_start();

private:
    std::vector<sf::Sound> m_sounds;
    std::vector<sf::SoundBuffer> m_sunds_buffers;
};


}// battle_ship namespace
