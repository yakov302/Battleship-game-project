#include "../inc/sound.hpp"

namespace battle_ship
{

namespace impl
{

void sound_initialization(std::vector<sf::Sound>& a_sounds, std::vector<sf::SoundBuffer>& a_sunds_buffers, std::ifstream& config_file)
{
    int i = 0;
    std::string sound_file_name;    
    while(std::getline(config_file, sound_file_name))
    {   
        a_sunds_buffers.emplace_back(sf::SoundBuffer());
        a_sunds_buffers[i].loadFromFile(sound_file_name);
        a_sounds.emplace_back(sf::Sound());
        a_sounds[i].setBuffer(a_sunds_buffers[i]);
        ++i;    
    }
}


}// namespace impl

Sound::Sound()
: m_sounds()
, m_sunds_buffers()
{
    m_sounds.reserve(NUM_OF_SOUNDS);
    m_sunds_buffers.reserve(NUM_OF_SOUNDS);
    std::ifstream sound_config_file("./resources/txt/sounds_config.txt");
    impl::sound_initialization(m_sounds, m_sunds_buffers, sound_config_file);
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
