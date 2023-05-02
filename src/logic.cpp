#include "../inc/logic.hpp"

namespace battle_ship
{

namespace impl
{

extern int rand_x(int x_base);
extern int rand_y(int y_base);

int give_me_smallest_ships_size(int* ships_sizes)
{
    if(ships_sizes[2] > 0)
        return 2;

    if(ships_sizes[3] > 0)
        return 3;

    return 4;
}

bool positive_random_loop(Matrix& matrix, int the_smallest_ship_size, int x, int y, bool x_or_y)
{
    int status;

    for(int i = 0; i < the_smallest_ship_size - 1; ++i)
    {
        if(x_or_y)
            status = matrix.give_status(x + SQUARE_SIZE*(i + 1), y);
        else
            status = matrix.give_status(x, y + SQUARE_SIZE*(i + 1));

        if(status == SHIP_HIT || status == EMPTY_HIT || status == OUTSIDE_MATRIX_RANGE)
            return false;
    }  

    return true;
}

bool negative_random_loop(Matrix& matrix, int the_smallest_ship_size, int x, int y, bool x_or_y)
{
    int status;
    int squares = 1;

    for(int i = the_smallest_ship_size - 1; i > 0; --i)
    {
        if(x_or_y)
            status = matrix.give_status(x - SQUARE_SIZE*(squares), y);
        else
            status = matrix.give_status(x, y - SQUARE_SIZE*(squares));

        if(status == SHIP_HIT || status == EMPTY_HIT || status == OUTSIDE_MATRIX_RANGE)
            return false;

        ++squares;
    }

    return true;
}

bool is_random_poin_makes_sense(Matrix& matrix, int* ships_sizes, int x, int y)
{
    int the_smallest_ship_size = give_me_smallest_ships_size(ships_sizes);

    if(positive_random_loop(matrix, the_smallest_ship_size, x, y, X))
        return true;
    if(positive_random_loop(matrix, the_smallest_ship_size, x, y, Y))
        return true;
    if(negative_random_loop(matrix, the_smallest_ship_size, x, y, X))
        return true;
    if(negative_random_loop(matrix, the_smallest_ship_size, x, y, Y))
        return true;

    return false;
}

int positive_loop(Matrix& matrix, int the_smallest_ship_size, int x, int y, bool x_or_y)
{
    int status;
    int counter = 0;

    for(int i = 0; i < the_smallest_ship_size - 1; ++i)
    {
        if(x_or_y)
            status = matrix.give_status(x + SQUARE_SIZE*(i + 1), y);
        else
            status = matrix.give_status(x, y + SQUARE_SIZE*(i + 1));

        if(status == EMPTY_HIT || status == OUTSIDE_MATRIX_RANGE)
            return counter;

        ++counter;
    }  

    return counter;
}

int negative_loop(Matrix& matrix, int the_smallest_ship_size, int x, int y, bool x_or_y)
{
    int status;
    int counter = 0;
    int squares = 1;

    for(int i = the_smallest_ship_size - 1; i > 0; --i)
    {
        if(x_or_y)
            status = matrix.give_status(x - (SQUARE_SIZE*squares), y);
        else
            status = matrix.give_status(x, y - (SQUARE_SIZE*squares));

        if(status == EMPTY_HIT || status == OUTSIDE_MATRIX_RANGE)
            return counter;

        ++squares;
        ++counter;
    }
    
    return counter;
}

bool is_the_poin_makes_sense(Matrix& matrix, int* ships_sizes, int x, int y, bool direction)
{
    int the_smallest_ship_size = give_me_smallest_ships_size(ships_sizes);

    if(direction == HORIZONTAL)
    {
        int right = positive_loop(matrix, the_smallest_ship_size, x, y, X);
        int left = negative_loop(matrix, the_smallest_ship_size, x, y, X);
        if(right + left + 1 >= the_smallest_ship_size)
            return true;
    }
    else
    {
        int right = positive_loop(matrix, the_smallest_ship_size, x, y, Y);
        int left = negative_loop(matrix, the_smallest_ship_size, x, y, Y);
        if(right + left + 1 >= the_smallest_ship_size)
            return true;
    }

    return false;
}

bool is_close_point_is_good(Matrix& matrix, int* ships_sizes, int x, int y, bool direction)
{
    int status = matrix.give_status(x, y);
    if((status == EMPTY || status == SHIP)
    && is_the_poin_makes_sense(matrix, ships_sizes, x, y, direction))
        return true;

    return false;
}

void set_ships_sizes_start_status(int* ships_sizes)
{
    for(int i = 0; i < SHIPS_MAX_SIZE; ++i)
        ships_sizes[i] = 0;

    ships_sizes[2] = 1;
    ships_sizes[3] = 3;
    ships_sizes[4] = 2;
}


}

Logic::Logic()
: m_hit_point(0,0)
, m_number_of_hits(0)
, m_hit_ship_direction(true)
, m_hit_play_direction(true)
{
    impl::set_ships_sizes_start_status(m_ships_sizes);
}

std::pair<int, int> Logic::random_point(Matrix& matrix, int* ships_sizes)
{
    int x = impl::rand_x(X_PLAYER_BASE);
    int y = impl::rand_y(Y_PLAYER_BASE);
    int status = matrix.give_status(x, y);

    while (status == SHIP_HIT
        || status == EMPTY_HIT
        || !impl::is_random_poin_makes_sense(matrix, ships_sizes, x, y))
    {
        x = impl::rand_x(X_PLAYER_BASE);
        y = impl::rand_y(Y_PLAYER_BASE);
        status = matrix.give_status(x, y);
    }
    
    return std::pair<int, int>(x, y);
}

std::pair<int, int> Logic::pick_close_point(Matrix& matrix)
{
    int x = m_hit_point.first + SQUARE_SIZE;
    int y = m_hit_point.second;
    if(impl::is_close_point_is_good(matrix, m_ships_sizes, x, y, HORIZONTAL))
        return std::pair<int, int>(x, y);

    x = m_hit_point.first - SQUARE_SIZE;
    y = m_hit_point.second;
    if(impl::is_close_point_is_good(matrix, m_ships_sizes, x, y, HORIZONTAL))
        return std::pair<int, int>(x, y);
    
    x = m_hit_point.first;
    y = m_hit_point.second + SQUARE_SIZE;;
    if(impl::is_close_point_is_good(matrix, m_ships_sizes, x, y, VERTICAL))
        return std::pair<int, int>(x, y);

    x = m_hit_point.first;
    y = m_hit_point.second - SQUARE_SIZE;;
    if(impl::is_close_point_is_good(matrix, m_ships_sizes, x, y, VERTICAL))
        return std::pair<int, int>(x, y);
    
    return std::pair<int, int>(x, y);
}

std::pair<int, int> Logic::pick_next_point_horizontal(Matrix& matrix)
{
    if(m_hit_play_direction == FORWARD)
    {
        if(impl::is_close_point_is_good(matrix, m_ships_sizes, m_hit_point.first + SQUARE_SIZE, m_hit_point.second, HORIZONTAL))
        {
            return std::pair<int, int>(m_hit_point.first + SQUARE_SIZE, m_hit_point.second);
        }
        else
        {
            m_hit_play_direction = BACKWARD;  
            m_hit_point.first -= m_number_of_hits*SQUARE_SIZE;
            return std::pair<int, int>(m_hit_point.first, m_hit_point.second);
        }
    }

    return std::pair<int, int>(m_hit_point.first - SQUARE_SIZE, m_hit_point.second);
}

std::pair<int, int> Logic::pick_next_point_vertical(Matrix& matrix)
{
    if(m_hit_play_direction == FORWARD)
    {
        if(impl::is_close_point_is_good(matrix, m_ships_sizes, m_hit_point.first, m_hit_point.second + SQUARE_SIZE, VERTICAL))
        {
            return std::pair<int, int>(m_hit_point.first, m_hit_point.second + SQUARE_SIZE);
        }
        else
        {
            m_hit_play_direction = BACKWARD;  
            m_hit_point.second -= m_number_of_hits*SQUARE_SIZE;
            return std::pair<int, int>(m_hit_point.first, m_hit_point.second);
        }
    }

    return std::pair<int, int>(m_hit_point.first, m_hit_point.second - SQUARE_SIZE);
}

std::pair<int, int> Logic::play(Matrix& matrix)
{
    if(m_number_of_hits < 1)
        return random_point(matrix, m_ships_sizes);

    if(m_number_of_hits == 1)
        return pick_close_point(matrix);

    if(m_hit_ship_direction == HORIZONTAL)
        return pick_next_point_horizontal(matrix);
    else
        return pick_next_point_vertical(matrix);
}

void Logic::ship_hit(int x, int y)
{
    ++m_number_of_hits;
    
    if(m_number_of_hits == 2)
    {
        if(x == m_hit_point.first)
        {
            m_hit_ship_direction = VERTICAL;

            if(y > m_hit_point.second)
                m_hit_play_direction = FORWARD;
            else
                m_hit_play_direction = BACKWARD;
        }

        if(y == m_hit_point.second)
        {
            m_hit_ship_direction = HORIZONTAL; 

            if(x > m_hit_point.first)
                m_hit_play_direction = FORWARD;
            else
                m_hit_play_direction = BACKWARD;
        }

    }

    m_hit_point = {x, y};
}

void Logic::empty_hit()
{
    if(m_number_of_hits > 1)
    {
        m_hit_play_direction = BACKWARD;
        
        if(m_hit_ship_direction == HORIZONTAL)
            m_hit_point.first -= (m_number_of_hits - 1)*SQUARE_SIZE;
        else
            m_hit_point.second -= (m_number_of_hits - 1)*SQUARE_SIZE;
    }
}

void Logic::ship_sink(int size)
{
    m_ships_sizes[size]--;
    m_number_of_hits = 0;
}


} // battle_ship namespace
