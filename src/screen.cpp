#include "../inc/screen.hpp"

namespace battle_ship
{

bool mouse_press_on_ship = false;

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

bool is_mouse_pressed_on_the_ship(ShipPtr& ship, int x, int y)
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left) && ship.get()->is_in_range(x, y);
}

void center_the_ship_on_the_mouse(ShipPtr& ship, int x, int y)
{
    ship.get()->set_position(x - (ship.get()->length()/2), y - (ship.get()->width()/2));
}


bool the_ship_is_off_the_grid_board(ShipPtr& ship)
{
    return 
    (
        ship.get()->left() < X_BASE  - SQUARE_SIZE/2                                 ||
        ship.get()->right() > X_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) + SQUARE_SIZE/2  ||
        ship.get()->top() < Y_BASE - SQUARE_SIZE/2                                   ||
        ship.get()->bottom() > Y_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) + SQUARE_SIZE/2
    );
}

int x(ShipPtr& ship)
{
    return ship.get()->left() - (ship.get()->left() - X_BASE)%SQUARE_SIZE;
}

int y(ShipPtr& ship)
{
    if(ship.get()->top() < Y_BASE)
    {
        if(ship.get()->bottom() > Y_BASE)
            return  Y_BASE + (SQUARE_SIZE - ship.get()->width()) + GAP;
        else    
          return  ship.get()->top();
    }
    else
    {
        return ship.get()->top() + (SQUARE_SIZE - (ship.get()->top() - (Y_BASE + GAP))%SQUARE_SIZE) + (SQUARE_SIZE - ship.get()->width());
    }
}

void set_ship_position(ShipPtr& ship)
{
    ship.get()->set_position(x(ship) + GAP, y(ship) - GAP);

    if(the_ship_is_off_the_grid_board(ship))
        ship.get()->set_position(X_START_POINT, Y_START_POINT);
}


}// impl namespace


Screen::Screen()
: m_window(sf::VideoMode::getDesktopMode(), "Battleship")

//need to by deleted
, m_ship1 (new Ship("resources/images/1.png", 4, 206,  182, 0.85, HORIZONTAL))
, m_ship4 (new Ship("resources/images/2.png", 3, 340,  445, 0.95,  HORIZONTAL))
, m_ship8 (new Ship("resources/images/3.png",   4, 240,  565, 0.49, VERTICAL))
, m_ship9 (new Ship("resources/images/4.png",   3, 215, 375, 0.65,  VERTICAL))
, m_ship10(new Ship("resources/images/5.png",   3, 820, 183, 1.15,  VERTICAL))
, m_ship11(new Ship("resources/images/6.png",   2, 820, 570, 0.85,  VERTICAL))
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

    //need to by deleted
    m_ship1.get()->draw(m_window);
    m_ship4.get()->draw(m_window);
    m_ship8.get()->draw(m_window);
    m_ship9.get()->draw(m_window);
    m_ship10.get()->draw(m_window);
    m_ship11.get()->draw(m_window);
}

void Screen::check_mouse()
{ 
    int x = impl::mouse_x_position(m_window);
    int y = impl::mouse_y_position(m_window);

    if(!mouse_press_on_ship)
    {
        if(impl::is_mouse_pressed_on_the_ship(m_ship11, x, y))
            mouse_press_on_ship = true;
    }
    else
    {
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mouse_press_on_ship = false;
            impl::set_ship_position(m_ship11);
        }
        else
        {
            impl::center_the_ship_on_the_mouse(m_ship11, x, y);
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

void Screen::run()
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


}// battle_ship namespace
