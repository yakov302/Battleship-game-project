#include "../inc/screen.hpp"

namespace battle_ship
{

int ship_index = 0;
int num_ship_sunk_player = 0;
int num_ship_sunk_rival = 0;
bool ship_direction = HORIZONTAL;
bool mouse_press_on_ship = false;
bool ships_location_phase = true;
bool my_turn = true;
bool end_game = false;

namespace impl
{

extern void increase_index(int* x, int* y, bool direction);

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
        ship_manager.x(i, direction)      < X_PLAYER_BASE - SQUARE_SIZE/2                                ||
        ship_manager.right(i, direction)  > X_PLAYER_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) + SQUARE_SIZE/2 ||
        ship_manager.y(i, direction)      < Y_PLAYER_BASE - SQUARE_SIZE/2                                ||
        ship_manager.bottom(i, direction) > Y_PLAYER_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) + SQUARE_SIZE/2
    );
}

int set_x_gap(bool direction, int size, int i, ShipManager& ship_manager)
{
    if(direction == HORIZONTAL)
        return size - ship_manager.length(i, direction); 
    else
        return SQUARE_SIZE - ship_manager.length(i, direction);
}

int set_y_gap(bool direction, int size, int i, ShipManager& ship_manager)
{
    if(direction == HORIZONTAL)
        return SQUARE_SIZE -  ship_manager.width(i, direction);
    else
        return size - ship_manager.width(i, direction);
}

std::pair<int, int> set_point(ShipManager& ship_manager, Matrix& matrix, int i, bool direction)
{
    int x = ship_manager.x(i, direction);
    int y = ship_manager.y(i, direction);
    if(direction == HORIZONTAL)
        y += ship_manager.width(i, direction);

    x = matrix.give_x(x, y);
    y = matrix.give_y(x, y);

    int gap;
    int size = ship_manager.size(i, direction)*SQUARE_SIZE;

    gap = set_x_gap(direction, size, i, ship_manager);
    x = x + gap/2 + GAP;

    gap = set_y_gap(direction, size, i, ship_manager);
    y = y + gap/2 + GAP;

    return std::pair<int, int>(x, y);
}

void set_matrix_status(int ship_index, bool direction, ShipManager& ship_manager, Matrix& matrix)
{
    int x = ship_manager.x(ship_index, direction);
    int y = ship_manager.y(ship_index, direction);
    int size = ship_manager.size(ship_index, direction);

    for(int i = 0; i < size; ++i)
    {
        matrix.set_square(x, y, SHIP, ship_index, direction);
        increase_index(&x, &y, direction);
    }

}

bool there_is_close_ship(int x, int y,  Matrix& matrix)
{
    if(matrix.give_status(x, y)               == SHIP
    || matrix.give_status(x + SQUARE_SIZE, y) == SHIP
    || matrix.give_status(x - SQUARE_SIZE, y) == SHIP
    || matrix.give_status(x, y + SQUARE_SIZE) == SHIP
    || matrix.give_status(x, y - SQUARE_SIZE) == SHIP)
        return true;
    return false;
}

bool the_ship_is_next_to_another_ship(int i, bool direction, ShipManager& ship_manager, Matrix& matrix)
{
    int x = ship_manager.x(i, direction);
    int y = ship_manager.y(i, direction);
    int size = ship_manager.size(i, direction);

    for(int i = 0; i < size; ++i)
    {
        if(there_is_close_ship(x, y, matrix))
            return true;
        increase_index(&x, &y, direction);
    }

    return false;
}

void check_end_game(Background& background)
{
    if(num_ship_sunk_player == 6)
    {
        background.set_message("rival won");
        end_game = true;
    }

    if(num_ship_sunk_rival == 6)
    {
        background.set_message("you won");
        end_game = true;
    }
}

void invalid_position(std::string message, int i, bool direction, ShipManager& ship_manager, Background& background)
{
    background.set_message(message);
    ship_manager.set_ship_position(i, direction, X_START_POINT - ship_manager.length(i, direction)/2, Y_START_POINT);
}

void set_ship_on_bord(int i, bool direction, ShipManager& ship_manager, Matrix& matrix, Background& background)
{
    mouse_press_on_ship = false;
    std::pair<int, int> point = set_point(ship_manager, matrix, i, direction); 
    ship_manager.set_ship_position(i, direction, point.first, point.second);

    if(the_ship_is_off_the_grid_board(ship_manager, i, direction))
    {
        invalid_position("Off the board", i, direction, ship_manager, background);
        return;
    }

    if(the_ship_is_next_to_another_ship(i, direction, ship_manager, matrix))
    {
        invalid_position("Not allowed near another ship", i, direction, ship_manager, background);
        return;
    }

    background.set_message("");
    set_matrix_status(i, direction, ship_manager, matrix);
    ship_manager.locate_ship(ship_index, ship_direction);
    ship_direction = HORIZONTAL;
    ++ship_index;
}

bool is_image_not_should_by_set(int status)
{
    return(status == OUTSIDE_MATRIX_RANGE
        || status == SHIP_HIT
        || status == EMPTY_HIT);
}

void place_x(Matrix& matrix, ImageManager& images, int x, int y)
{
    if(matrix.give_status(x + SQUARE_SIZE, y) == EMPTY)
    {
        matrix.set_status(x + SQUARE_SIZE, y, EMPTY_HIT);
        images.set_x(x + SQUARE_SIZE, y);
    }
    
    if(matrix.give_status(x - SQUARE_SIZE, y) == EMPTY)
    {
        matrix.set_status(x - SQUARE_SIZE, y, EMPTY_HIT);
        images.set_x(x - SQUARE_SIZE, y);
    }

    if(matrix.give_status(x, y + SQUARE_SIZE) == EMPTY)
    {
        matrix.set_status(x, y + SQUARE_SIZE, EMPTY_HIT);
        images.set_x(x, y + SQUARE_SIZE);
    }
    
    if(matrix.give_status(x, y - SQUARE_SIZE) == EMPTY)
    {
        matrix.set_status(x, y - SQUARE_SIZE, EMPTY_HIT);
        images.set_x(x, y - SQUARE_SIZE);
    }
}

void sink_ship(int x, int y, int size, bool direction, Matrix& matrix, ImageManager& images)
{
    for(int i = 0; i < size; ++i)
    {
        impl::place_x(matrix, images, x, y);
        impl::increase_index(&x, &y, direction);
    }
}

void handle_mouse_pressed(Matrix& matrix, ImageManager& images, Rival& rival, int x, int y, Background& background)
{
    int status = matrix.give_status(x, y);
    if(is_image_not_should_by_set(status))
        return;

    my_turn = !my_turn;

    if(status == SHIP)
    {
        matrix.set_status(x, y, SHIP_HIT);
        images.set_fire(matrix.give_x(x, y), matrix.give_y(x, y));

        int index = matrix.give_ship_index(x, y);
        if(rival.hit(matrix.give_ship_index(x, y)))
        {
            sink_ship(rival.x(index), rival.y(index), rival.ship_size(index), rival.ship_direction(index), matrix, images);
            ++num_ship_sunk_rival;
            check_end_game(background);
        }
    }
    else
    {
        matrix.set_status(x, y, EMPTY_HIT);
        images.set_x(matrix.give_x(x, y), matrix.give_y(x, y));
    }
}

void rival_play(Matrix& matrix, ImageManager& images, ShipManager& ship_manager, Rival& rival, Background& background)
{
    sleep(1);
    
    std::pair<int, int> point = rival.play(matrix);
    int status = matrix.give_status(point.first, point.second);

    if(status == SHIP)
    {
        rival.player_ship_hit(point.first, point.second);
        matrix.set_status(point.first, point.second, SHIP_HIT);
        images.set_fire(matrix.give_x(point.first, point.second), matrix.give_y(point.first, point.second));

        int index = matrix.give_ship_index(point.first, point.second);
        bool direction = matrix.give_direction(point.first, point.second);
        if(ship_manager.hit(matrix.give_ship_index(point.first, point.second)))
        {
            sink_ship(ship_manager.x(index, direction), 
                      ship_manager.y(index, direction), 
                      ship_manager.size(index, direction), 
                      direction, matrix, images);
            
            ship_manager.sink_the_ship(index, direction);
            ++num_ship_sunk_player;
            rival.ship_sink();
            check_end_game(background);
        }
    }
    else
    {
        rival.empty_hit();
        matrix.set_status(point.first, point.second, EMPTY_HIT);
        images.set_x(matrix.give_x(point.first, point.second), matrix.give_y(point.first, point.second));
    }

    my_turn = !my_turn;
}


}// impl namespace


Screen::Screen()
: m_window(sf::VideoMode::getDesktopMode(), "Battleship")
, m_rival()
, m_player_matrix(X_PLAYER_BASE, Y_PLAYER_BASE)        
, m_rival_matrix(X_RIVAL_BASE, Y_RIVAL_BASE)
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
    m_image_manager.draw(m_window);
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
            impl::set_ship_on_bord(ship_index, ship_direction, m_ships_manager, m_player_matrix, m_background);
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
    int x = impl::mouse_x_position(m_window);
    int y = impl::mouse_y_position(m_window);

    if(!my_turn)
        impl::rival_play(m_player_matrix, m_image_manager, m_ships_manager, m_rival, m_background);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && my_turn)
        impl::handle_mouse_pressed(m_rival_matrix, m_image_manager, m_rival, x, y, m_background);
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

    m_rival.place_the_ships_on_board(m_rival_matrix);
    ships_location_phase = false;
}

void Screen::game_loop()
{
    while(m_window.isOpen() && !end_game)
    {
        m_window.clear();
        draw_game();
        check_mouse_game();
        draw_game();
        check_events();
        m_window.display();
    }
}

void Screen::run()
{
    locate_loop();
    game_loop();
    sleep(5);
    stop();
}


}// battle_ship namespace
