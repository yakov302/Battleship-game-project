#include "../inc/sound.hpp"

namespace battle_ship
{

namespace impl
{

void sound_initialization(std::vector<sf::Sound>& a_sounds, std::vector<sf::SoundBuffer>& a_sunds_buffers)
{
    for(int i = 0; i < NUM_OF_SOUNDS; i++)
        a_sunds_buffers.emplace_back(sf::SoundBuffer());

    a_sunds_buffers[0].loadFromFile("./resources/sounds/invalid.wav");
    a_sunds_buffers[1].loadFromFile("./resources/sounds/anchor.wav");
    a_sunds_buffers[2].loadFromFile("./resources/sounds/button.wav");
    a_sunds_buffers[3].loadFromFile("./resources/sounds/empty_hit.wav");
    a_sunds_buffers[4].loadFromFile("./resources/sounds/hit.wav");
    a_sunds_buffers[5].loadFromFile("./resources/sounds/sinking.wav");
    a_sunds_buffers[6].loadFromFile("./resources/sounds/win.wav");
    a_sunds_buffers[7].loadFromFile("./resources/sounds/fail.wav");
    a_sunds_buffers[8].loadFromFile("./resources/sounds/start.wav");

    for(int i = 0; i < NUM_OF_SOUNDS; i++)
    {
        a_sounds.emplace_back(sf::Sound());
        a_sounds[i].setBuffer(a_sunds_buffers[i]);
    }
}


}// namespace impl

Sound::Sound()
: m_sounds()
, m_sunds_buffers()
{
    m_sounds.reserve(NUM_OF_SOUNDS);
    m_sunds_buffers.reserve(NUM_OF_SOUNDS);
    impl::sound_initialization(m_sounds, m_sunds_buffers);
}

void Sound::play_invalid()
{
    m_sounds[0].play();
}

void Sound::play_anchor()
{
    m_sounds[1].play();
}

void Sound::play_button()
{
    m_sounds[2].play();
}

void Sound::play_empty_hit()
{
    m_sounds[3].play();
}

void Sound::play_hit()
{
    m_sounds[4].play();
}

void Sound::play_sinking()
{
    m_sounds[5].play();
}

void Sound::play_win()
{
    m_sounds[6].play();
}

void Sound::play_fail()
{
    m_sounds[7].play();
}

void Sound::play_start()
{
    m_sounds[8].play();
}


}// poker namespace