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

    map[i] = RivalShip{size, 0, i, direction};
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

bool the_ship_is_next_to_another_ship(int x, int y, int size, bool direction, Matrix& matrix)
{
    if(direction == HORIZONTAL)
    {
        for(int i = 0; i < size; ++i)
        {
            if(there_is_close_ship(x, y, matrix))
                return true;
            x += SQUARE_SIZE;
        }
    }
    else
    {
        for(int i = 0; i < size; ++i)
        {
            if(there_is_close_ship(x, y, matrix))
                return true;
            y += SQUARE_SIZE;
        }
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

int rand_x()
{
    int x = distribution(seed_engine)%9;
    return X_RIVAL_BASE + x*SQUARE_SIZE;
}

int rand_y()
{
    int y = distribution(seed_engine)%9;
    return Y_RIVAL_BASE + y*SQUARE_SIZE;
}

void check_if_point_valid(int* x, int* y, int size, bool direction, Matrix& matrix)
{
    while(impl::the_ship_is_next_to_another_ship(*x, *y, size, direction, matrix) 
        ||impl::the_ship_is_off_the_grid_board(*x, *x + size*SQUARE_SIZE, *y, *y + SQUARE_SIZE))
    {
        *x = impl::rand_x();
        *y = impl::rand_y();
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

void Rival::place_the_ships_on_board(Matrix& matrix)
{
    for(int ship_index = 0; ship_index < NUM_OF_SHIPS; ++ship_index)
    {
        int x = impl::rand_x();
        int y = impl::rand_y();
        int size = m_horizontal[ship_index].size;
        bool direction = distribution(seed_engine)%2;

        if(direction == HORIZONTAL)
        {
            impl::check_if_point_valid(&x, &y, size, direction, matrix);
            std::cout << "size: " << size << "\n";
            for(int i = 0; i < size; ++i)
            {
                matrix.set_square(x, y, SHIP, ship_index);
                x += SQUARE_SIZE;
            }
            std::cout << matrix << "\n";
        }
        else
        {
            impl::check_if_point_valid(&x, &y, size, direction, matrix);
            std::cout << "size: " << size << "\n";
            for(int i = 0; i < size; ++i)
            {
                matrix.set_square(x, y, SHIP, ship_index);
                y += SQUARE_SIZE;
            }
            std::cout << matrix << "\n";
        }
    }
}

void Rival::hit (int i)
{
    m_locate_ships[i].hits++;
    if(m_locate_ships[i].hits == m_locate_ships[i].size)
        m_locate_ships.erase(i);
}


}//battle_ship namespace