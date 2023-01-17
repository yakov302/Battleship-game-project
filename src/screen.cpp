#include "../inc/screen.hpp"

namespace battle_ship
{

namespace impl
{

static void* thread_function(void* arg)
{
    Screen* screen = static_cast<Screen*>(arg);
    screen->run();
    return 0;
}

}// impl namespace


Screen::Screen()
: m_window(sf::VideoMode::getDesktopMode(), "Battleship")

//need to by deleted
, m_ship1 (new Ship("resources/images/ship_4_a_horizontal.png", 4, 135,  158, 1.15, HORIZONTAL))
, m_ship2 (new Ship("resources/images/ship_4_b_horizontal.png", 4, 330,  250, 1.15, HORIZONTAL))
, m_ship3 (new Ship("resources/images/ship_3_a_horizontal.png", 3, 335,  375, 1.1,  HORIZONTAL))
, m_ship4 (new Ship("resources/images/ship_3_b_horizontal.png", 3, 335,  440, 1.2,  HORIZONTAL))
, m_ship5 (new Ship("resources/images/ship_2_a_horizontal.png", 2, 340,  565, 1.3,  HORIZONTAL))
, m_ship6 (new Ship("resources/images/ship_2_b_horizontal.png", 2, 335,  630, 1,    HORIZONTAL))
, m_ship7 (new Ship("resources/images/ship_4_a_vertical.png",   4, 800,  185, 1.15, VERTICAL))
, m_ship8 (new Ship("resources/images/ship_4_b_vertical.png",   4, 900,  250, 1.15, VERTICAL))
, m_ship9 (new Ship("resources/images/ship_3_a_vertical.png",   3, 1000, 375, 1.1,  VERTICAL))
, m_ship10(new Ship("resources/images/ship_3_b_vertical.png",   3, 1100, 440, 1.2,  VERTICAL))
, m_ship11(new Ship("resources/images/ship_2_a_vertical.png",   2, 1200, 565, 1.3,  VERTICAL))
, m_ship12(new Ship("resources/images/ship_2_b_vertical.png",   2, 1300, 630, 1,    VERTICAL))

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
    m_ship2.get()->draw(m_window);
    m_ship3.get()->draw(m_window);
    m_ship4.get()->draw(m_window);
    m_ship5.get()->draw(m_window);
    m_ship6.get()->draw(m_window);
    m_ship7.get()->draw(m_window);
    m_ship8.get()->draw(m_window);
    m_ship9.get()->draw(m_window);
    m_ship10.get()->draw(m_window);
    m_ship11.get()->draw(m_window);
    m_ship12.get()->draw(m_window);
}

void Screen::check_mouse()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {    

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
