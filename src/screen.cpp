#include "../inc/screen.hpp"

namespace battle_ship
{

int ship_index = 0;
bool ship_direction = HORIZONTAL;
bool mouse_press_on_ship = false;
bool ships_location_phase = true;

namespace impl
{

static void* thread_function(void* arg)
{
    Screen* screen = static_cast<Screen*>(arg);
    screen->run();
    return 0;
}

int mouse_x_position(sf::RenderWindow& window)
{
    sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
    sf::Vector2f position = window.mapPixelToCoords(pixel_pos); 
    return position.x;
}

int mouse_y_position(sf::RenderWindow& window)
{
    sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
    sf::Vector2f position = window.mapPixelToCoords(pixel_pos); 
    return position.y;
}

void center_the_ship_on_the_mouse(ShipManager& ship_manager, int i, bool direction, int x, int y)
{
    ship_manager.set_ship_position(i, direction, x - (ship_manager.length(i, direction)/2), y - (ship_manager.width(i, direction)/2));
}

bool the_ship_is_off_the_grid_board(ShipManager& ship_manager, int i, bool direction)
{
    return 
    (
        ship_manager.left(i, direction)   < X_BASE - SQUARE_SIZE/2                                 ||
        ship_manager.right(i, direction)  > X_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) + SQUARE_SIZE/2  ||
        ship_manager.top(i, direction)    < Y_BASE - SQUARE_SIZE/2                                 ||
        ship_manager.bottom(i, direction) > Y_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) + SQUARE_SIZE/2
    );
}

std::pair<int, int> set_point(ShipManager& ship_manager, Matrix& matrix, int i, bool direction)
{
    int x = ship_manager.left(i, direction);
    int y = ship_manager.top(i, direction);
    if(direction == HORIZONTAL)
        y += ship_manager.width(i, direction);

    int index = matrix.give_index(x, y);
    x = matrix.give_x(index);
    y = matrix.give_y(index);

    int gap;
    int size = ship_manager.size(i, direction)*SQUARE_SIZE;

    if(direction == HORIZONTAL)
        gap = size - ship_manager.length(i, direction); 
    else
        gap = SQUARE_SIZE - ship_manager.length(i, direction);
    x = x + gap/2;

    if(direction == HORIZONTAL)
        gap = SQUARE_SIZE -  ship_manager.width(i, direction);
    else
        gap = size - ship_manager.width(i, direction);
    y = y + gap/2;

    return std::pair<int, int>(x, y);
}

void set_ship_on_bord(int i, bool direction, ShipManager& ship_manager, Matrix& matrix)
{
    mouse_press_on_ship = false;
    std::pair<int, int> point = set_point(ship_manager, matrix, i, direction); 
    ship_manager.set_ship_position(i, direction, point.first, point.second);

    if(the_ship_is_off_the_grid_board(ship_manager, i, direction))
    {
        ship_manager.set_ship_position(i, direction, X_START_POINT - ship_manager.length(i, direction)/2, Y_START_POINT);
    }
    else
    {
        ship_manager.locate_ship(ship_index, ship_direction);
        ship_direction = HORIZONTAL;
        ++ship_index;
   }
}


}// impl namespace


Screen::Screen()
: m_window(sf::VideoMode::getDesktopMode(), "Battleship")
{
    m_thread = new std::thread(impl::thread_function, this);
}

Screen::~Screen()
{
    m_thread->join();
    delete m_thread;
}

void Screen::stop()
{
    m_window.close();
}

void Screen::draw_locate()
{
    m_background.draw(m_window);
    m_ships_manager.draw_located_ships(m_window);
    m_ships_manager.draw_ship(ship_index, ship_direction, m_window);
}

void Screen::draw_game()
{
    m_background.draw(m_window);
    m_ships_manager.draw_located_ships(m_window);
}

void Screen::check_mouse_locate()
{ 
    int x = impl::mouse_x_position(m_window);
    int y = impl::mouse_y_position(m_window);

    if(mouse_press_on_ship)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            impl::center_the_ship_on_the_mouse(m_ships_manager, ship_index, ship_direction, x, y);
        else
            impl::set_ship_on_bord(ship_index, ship_direction, m_ships_manager, m_player_matrix);
    }
    else
    {
        if(m_ships_manager.is_mouse_pressed_on_the_ship(ship_index, ship_direction, x, y))
            mouse_press_on_ship = true;
    }

    if(m_background.is_change_direction_button_pressed(x, y))
    {
        ship_direction = !ship_direction;
        usleep(250000);
    }
}

void Screen::check_mouse_game()
{ 

}

void Screen::check_events()
{
    m_window.pollEvent(m_event);

    switch (m_event.type)
    {
    case sf::Event::Closed:
        stop();
        break;
    
    default:
        break;
    }
}

void Screen::locate_loop()
{
    while(m_window.isOpen() && ship_index < NUM_OF_SHIPS)
    {
        m_window.clear();
        draw_locate();
        check_mouse_locate();
        check_events();
        m_window.display();
    }

    ships_location_phase = false;
}

void Screen::game_loop()
{
    while(m_window.isOpen())
    {
        m_window.clear();
        draw_game();
        check_mouse_game();
        check_events();
        m_window.display();
    }
}

void Screen::run()
{
    locate_loop();
    game_loop();
}


}// battle_ship namespace
