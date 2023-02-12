#include "../inc/screen.hpp"

namespace battle_ship
{

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
    ship_manager.set_ship_position(i, direction, x - (ship_manager.left(i, direction)/2), y - (ship_manager.width(i, direction)/2));
}

bool the_ship_is_off_the_grid_board(ShipManager& ship_manager, int i, bool direction)
{
    return 
    (
        ship_manager.left(i, direction) < X_BASE  - SQUARE_SIZE/2                                 ||
        ship_manager.right(i, direction) > X_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) + SQUARE_SIZE/2  ||
        ship_manager.top(i, direction) < Y_BASE - SQUARE_SIZE/2                                   ||
        ship_manager.bottom(i, direction) > Y_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) + SQUARE_SIZE/2
    );
}

int x(ShipManager& ship_manager, int i, bool direction)
{
    return ship_manager.left(i, direction) - (ship_manager.left(i, direction) - X_BASE)%SQUARE_SIZE;
}

int y(ShipManager& ship_manager, int i, bool direction)
{
    if(ship_manager.top(i, direction) < Y_BASE)
    {
        if(ship_manager.bottom(i, direction) > Y_BASE)
            return  Y_BASE + (SQUARE_SIZE - ship_manager.width(i, direction)) + GAP;
        else    
          return  ship_manager.top(i, direction);
    }
    else
    {
        return ship_manager.top(i, direction) + (SQUARE_SIZE - (ship_manager.top(i, direction) - (Y_BASE + GAP))%SQUARE_SIZE) + (SQUARE_SIZE - ship_manager.width(i, direction));
    }
}

void set_ship_position(int i, bool direction, ShipManager& ship_manager)
{
    ship_manager.set_ship_position(i, direction, x(ship_manager, i, direction) + GAP, y(ship_manager, i, direction) - GAP);

    if(the_ship_is_off_the_grid_board(ship_manager, i, direction))
        ship_manager.set_ship_position(i, direction, X_START_POINT, Y_START_POINT);
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

void Screen::draw_all()
{
    m_background.draw(m_window);
    m_ships_manager.print_ship(0, 0, m_window);
}

void Screen::check_mouse()
{ 
    int x = impl::mouse_x_position(m_window);
    int y = impl::mouse_y_position(m_window);

    if(!mouse_press_on_ship)
    {
        if(m_ships_manager.is_mouse_pressed_on_the_ship(0, 0, x, y))
            mouse_press_on_ship = true;
    }
    else
    {
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mouse_press_on_ship = false;
            impl::set_ship_position(0, 0, m_ships_manager);
        }
        else
        {
            impl::center_the_ship_on_the_mouse(m_ships_manager, 0, 0, x, y);
        }
    }
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

void Screen::ships_location_phase_loop()
{
    while(m_window.isOpen())
    {
        m_window.clear();
        draw_all();
        check_mouse();
        check_events();
        m_window.display();
    }
}

void Screen::run()
{
    ships_location_phase_loop();
    //game_phase_loop();
}


}// battle_ship namespace
