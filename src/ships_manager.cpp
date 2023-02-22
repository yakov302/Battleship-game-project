#include "../inc/ships_manager.hpp"

namespace battle_ship
{

namespace impl
{

int end = 0;
int begine = 0;

std::string next_slice_from_line(std::string& config_data)
{
    begine = end + 1;
    end = config_data.find('|', begine);
    return config_data.substr(begine, end-begine);
}

void set_position(ShipPtr& ship)
{
    ship.get()->set_position(X_START_POINT - ship.get()->length()/2, Y_START_POINT);
}

void load_ship(ShipsMap& map, std::string& config_data, int i)
{
    end = -1;
    begine = 0;

    std::string image_path = next_slice_from_line(config_data);
    int size = std::stoi(next_slice_from_line(config_data));
    int x_pos = std::stoi(next_slice_from_line(config_data));
    int y_pos = std::stoi(next_slice_from_line(config_data));
    float scale = std::stof(next_slice_from_line(config_data));
    bool direction = std::stoi(next_slice_from_line(config_data));

    map[i] = ShipPtr(new Ship(image_path, size, x_pos, y_pos, scale, direction));
    set_position(map[i]);
}

void load_ships(ShipsMap& map, std::ifstream& config_file)
{
    int i = 0;
    std::string line;    
    while(std::getline(config_file, line))
    {        
        load_ship(map, line, i); 
        ++i;    
    }
}


}//impl namespace

ShipManager::ShipManager()
{
    std::ifstream vertical_ships_config("./resources/txt/vertical_ships_config.txt");
    std::ifstream horizontal_ships_config("./resources/txt/horizontal_ships_config.txt");
    impl::load_ships(m_vertical, vertical_ships_config);
    impl::load_ships(m_horizontal, horizontal_ships_config);
}

void ShipManager::draw_ship(int i, bool direction, sf::RenderWindow& window)
{
    if(direction == HORIZONTAL)
        m_horizontal[i].get()->draw(window);
    else
        m_vertical[i].get()->draw(window);
}

void ShipManager::draw_located_ships(sf::RenderWindow& window)
{
    for(auto ship : m_locate_ships)
        ship.second.get()->draw(window);
}

bool ShipManager::is_mouse_pressed_on_the_ship(int i, bool direction, int x, int y)
{
    if(direction == HORIZONTAL)
        return sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_horizontal[i].get()->is_in_range(x, y);
    else
         return sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_vertical[i].get()->is_in_range(x, y);
}

void ShipManager::set_ship_position(int i, bool direction, int x, int y)
{
    if(direction == HORIZONTAL)
        m_horizontal[i].get()->set_position(x, y);
    else
        m_vertical[i].get()->set_position(x, y);
}

int ShipManager::x(int i, bool direction)
{
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->x();
    else
        return m_vertical[i].get()->x();
}

int ShipManager::y(int i, bool direction)
{
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->y();
    else
        return m_vertical[i].get()->y();
}

int ShipManager::left(int i, bool direction)
{
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->left();
    else
        return m_vertical[i].get()->left();
}

int ShipManager::right (int i, bool direction)
{    
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->right();
    else
        return m_vertical[i].get()->right(); 
}

int ShipManager::top(int i, bool direction)
{   
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->top();
    else
        return m_vertical[i].get()->top();
}

int ShipManager::bottom(int i, bool direction)
{
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->bottom();
    else
        return m_vertical[i].get()->bottom();
}

int ShipManager::width(int i, bool direction)
{
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->width();
    else
        return m_vertical[i].get()->width();
}

int ShipManager::length (int i, bool direction)
{
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->length();
    else
        return m_vertical[i].get()->length(); 
}

int ShipManager::size (int i, bool direction)
{
    if(direction == HORIZONTAL)
        return m_horizontal[i].get()->size();
    else
        return m_vertical[i].get()->size(); 
}

void ShipManager::locate_ship(int i, bool direction)
{
    if(direction == HORIZONTAL)
        m_locate_ships[i] = m_horizontal[i];
    else
        m_locate_ships[i] = m_vertical[i];
}

void ShipManager::hit (int i)
{
    m_locate_ships[i].get()->hit();
    if(m_locate_ships[i].get()->is_the_ship_sank())
        m_locate_ships.erase(i);
}


}//battle_ship namespace