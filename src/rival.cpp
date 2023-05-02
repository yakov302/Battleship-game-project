#include "../inc/rival.hpp"

namespace battle_ship
{

std::random_device seed;    
static std::mt19937_64 seed_engine(seed());
std::uniform_int_distribution<int> distribution;

namespace impl
{

extern int end;
extern int begine;
extern bool there_is_close_ship(int x, int y,  Matrix& matrix);
extern std::string next_slice_from_line(std::string& config_data);

void load_ship(RivalShipsMap& map, std::string& config_data, int i)
{
    end = -1;
    begine = 0;

    next_slice_from_line(config_data);
    int size = std::stoi(next_slice_from_line(config_data));
    for(int i = 0; i < 3; ++i)
        next_slice_from_line(config_data);
    bool direction = std::stoi(next_slice_from_line(config_data));

    map[i] = RivalShip{0, 0, size, 0, i, direction};
}

void load_ships(RivalShipsMap& map, std::ifstream& config_file)
{
    int i = 0;
    std::string line;    
    while(std::getline(config_file, line))
    {        
        load_ship(map, line, i); 
        ++i;    
    }
}

void increase_index(int* x, int* y, bool direction)
{
    if(direction == HORIZONTAL)
        *x += SQUARE_SIZE;
    else
        *y += SQUARE_SIZE;
}

bool the_ship_is_next_to_another_ship(int x, int y, int size, bool direction, Matrix& matrix)
{
    for(int i = 0; i < size; ++i)
    {
        if(there_is_close_ship(x, y, matrix))
            return true;
        increase_index(&x, &y, direction);
    }

    return false;
}

bool the_ship_is_off_the_grid_board(int left, int right, int top, int bottom)
{
    return 
    (
        left   < X_RIVAL_BASE                                 ||
        right  > X_RIVAL_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE)  ||
        top    < Y_RIVAL_BASE                                 ||
        bottom > Y_RIVAL_BASE + (NUM_OF_COLUMNS*SQUARE_SIZE) 
    );
}

void set_right_and_bottom(int* right, int* bottom, int x, int y, int size, bool direction)
{
    if(direction == HORIZONTAL)
    {
        *right = x + size*SQUARE_SIZE; 
        *bottom = y + SQUARE_SIZE;
    }
    else
    {
        *right = x + SQUARE_SIZE; 
        *bottom = y + size*SQUARE_SIZE;
    }
}

int rand_x(int x_base)
{
    int x = distribution(seed_engine)%10;
    return x_base + x*SQUARE_SIZE;
}

int rand_y(int y_base)
{
    int y = distribution(seed_engine)%10;
    return y_base + y*SQUARE_SIZE;
}

void check_if_point_valid(int* x, int* y, int size, bool direction, Matrix& matrix)
{
    int right, bottom;
    set_right_and_bottom(&right, &bottom, *x, *y, size, direction);

    while(impl::the_ship_is_next_to_another_ship(*x, *y, size, direction, matrix) 
        ||impl::the_ship_is_off_the_grid_board(*x, right, *y, bottom))
    {
        *x = impl::rand_x(X_RIVAL_BASE);
        *y = impl::rand_y(Y_RIVAL_BASE);
        set_right_and_bottom(&right, &bottom, *x, *y, size, direction);
    }
}


}//impl namespace

Rival::Rival()
{
    std::ifstream vertical_ships_config("./resources/txt/vertical_ships_config.txt");
    std::ifstream horizontal_ships_config("./resources/txt/horizontal_ships_config.txt");
    impl::load_ships(m_vertical, vertical_ships_config);
    impl::load_ships(m_horizontal, horizontal_ships_config);
}

void Rival::locate_ship(int i, int direction, int x, int y)
{
    if(direction == HORIZONTAL)
        m_locate_ships[i] = m_horizontal[i];
    else
        m_locate_ships[i] = m_vertical[i];

    m_locate_ships[i].x = x;
    m_locate_ships[i].y = y;
}

void Rival::place_the_ships_on_board(Matrix& matrix)
{
    for(int ship_index = 0; ship_index < NUM_OF_SHIPS; ++ship_index)
    {
        int x = impl::rand_x(X_RIVAL_BASE);
        int y = impl::rand_y(Y_RIVAL_BASE);
        int size = m_horizontal[ship_index].size;
        bool direction = distribution(seed_engine)%2;

        impl::check_if_point_valid(&x, &y, size, direction, matrix);
        locate_ship(ship_index, direction, x, y);

        for(int i = 0; i < size; ++i)
        {
            matrix.set_square(x, y, SHIP, ship_index, direction);
            impl::increase_index(&x, &y, direction);
        }
    }
}

int Rival::x(int i)
{
    return m_locate_ships[i].x;
}

int Rival::y(int i)
{    
    return m_locate_ships[i].y;
}

int Rival::ship_size(int index)
{
    return m_horizontal[index].size;
}

bool Rival::ship_direction(int index)
{
    return m_locate_ships[index].direction;
}

bool Rival::hit (int i)
{
    m_locate_ships[i].hits++;
    if(m_locate_ships[i].hits == m_locate_ships[i].size)
        return true;
    return false;
}

std::pair<int, int> Rival::play(Matrix& matrix)
{
    return m_logic.play(matrix);
}

void Rival::empty_hit()
{
    m_logic.empty_hit();
}

void Rival::ship_sink(int index)
{
    m_logic.ship_sink(m_locate_ships[index].size);
}

void Rival::player_ship_hit(int x, int y)
{
    m_logic.ship_hit(x, y);
}


}//battle_ship namespace
