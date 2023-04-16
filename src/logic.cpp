#include "../inc/logic.hpp"

namespace battle_ship
{

namespace impl
{

extern int rand_x(int x_base);
extern int rand_y(int y_base);


}

Logic::Logic()
: m_hit_point(0,0)
, m_number_of_hits(0)
, m_hit_ship_direction(true)
, m_hit_play_direction(true)
{

}

std::pair<int, int> Logic::random_point(Matrix& matrix)
{
    int x = impl::rand_x(X_PLAYER_BASE);
    int y = impl::rand_y(Y_PLAYER_BASE);
    int status = matrix.give_status(x, y);

    while (status == SHIP_HIT
        || status == EMPTY_HIT)
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
    int status = matrix.give_status(x, y);
    if(status == EMPTY
    || status == SHIP)
        return std::pair<int, int>(x, y);

    x = m_hit_point.first - SQUARE_SIZE;
    y = m_hit_point.second;
    status = matrix.give_status(x, y);
    if(status == EMPTY
    || status == SHIP)
        return std::pair<int, int>(x, y);
    
    x = m_hit_point.first;
    y = m_hit_point.second + SQUARE_SIZE;;
    status = matrix.give_status(x, y);
    if(status == EMPTY
    || status == SHIP)
        return std::pair<int, int>(x, y);

    x = m_hit_point.first;
    y = m_hit_point.second - SQUARE_SIZE;;
    status = matrix.give_status(x, y);
    if(status == EMPTY
    || status == SHIP)
        return std::pair<int, int>(x, y);
    
    return std::pair<int, int>(x, y);
}

std::pair<int, int> Logic::play(Matrix& matrix)
{
    if(m_number_of_hits < 1)
        return random_point(matrix);

    if(m_number_of_hits == 1)
        return pick_close_point(matrix);

    if(m_hit_ship_direction == HORIZONTAL)
    {
        if(m_hit_play_direction == FORWARD)
            return std::pair<int, int>(m_hit_point.first + SQUARE_SIZE, m_hit_point.second);
        else
            return std::pair<int, int>(m_hit_point.first - SQUARE_SIZE, m_hit_point.second);
    }
    else
    {
         if(m_hit_play_direction == FORWARD)
            return std::pair<int, int>(m_hit_point.first, m_hit_point.second  + SQUARE_SIZE);
        else
            return std::pair<int, int>(m_hit_point.first, m_hit_point.second - SQUARE_SIZE);       
    }
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

void Logic::ship_sink()
{
    m_number_of_hits = 0;
}


}//battle_ship namespace