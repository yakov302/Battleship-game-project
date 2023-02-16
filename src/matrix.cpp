#include "../inc/matrix.hpp"

namespace battle_ship
{

namespace impl
{

int get_index(int x, int y)
{
    return NUM_OF_COLUMNS*x + y;
}
   
void init_matrix(Square* buffer)
{
    for(int i = 0; i < NUM_OF_COLUMNS; ++i)
    {
        for(int j = 0; j < NUM_OF_COLUMNS; ++j)
        {
            buffer[get_index(i, j)].x = X_BASE + SQUARE_SIZE*j;
            buffer[get_index(i, j)].y = Y_BASE + SQUARE_SIZE*i;
            buffer[get_index(i, j)].status = EMPTY;
        }
    }
}

int is_index_inside_matrix_range(int index)
{

    if(index >= NUM_OF_POINTS || index < 0)
        return false;
    return true;
}

int is_point_inside_matrix_range(int x, int y)
{
    if(x < X_BASE || y <  Y_BASE || x > X_BASE + SQUARE_SIZE*NUM_OF_COLUMNS || y > Y_BASE + SQUARE_SIZE*NUM_OF_COLUMNS)
        return false;
    return true;
}


}//impl namespace

Matrix::Matrix()
{
    impl::init_matrix(m_matrix);
}

int Matrix::get_status(int x, int y)
{
    int index = give_index(x, y);
    if(! impl::is_index_inside_matrix_range(index))
        return OUTSIDE_MATRIX_RANGE;
    return m_matrix[index].status;
}

void Matrix::set_status(int x, int y, int value)
{
    int index = give_index(x, y);
    if(!impl::is_index_inside_matrix_range(index))
        return;
    m_matrix[index].status = value;
}

int Matrix::give_index(int x, int y)
{
    if(! impl::is_point_inside_matrix_range(x, y))
        return OUTSIDE_MATRIX_RANGE;

    for(int i = 0; i < NUM_OF_COLUMNS; ++i)
    {
        for(int j = 0; j < NUM_OF_COLUMNS; ++j)
        {
            if(y >= give_y(impl::get_index(i, j)) + SQUARE_SIZE)
                break;
            
            if(x >= give_x(impl::get_index(i, j)) + SQUARE_SIZE)
                continue;
            
            return impl::get_index(i, j);
        }
    }

    return OUTSIDE_MATRIX_RANGE; //Shouldn't get here
}

int Matrix::give_x(int index)
{
    if(! impl::is_index_inside_matrix_range(index))
         return OUTSIDE_MATRIX_RANGE;
    return m_matrix[index].x;
}

int Matrix::give_y(int index)
{
    if(! impl::is_index_inside_matrix_range(index))
         return OUTSIDE_MATRIX_RANGE;
    return m_matrix[index].y;
}

std::ostream& operator<<(std::ostream& a_os, Matrix const& matrix)
{
    for(int i = 0; i < NUM_OF_COLUMNS; ++i)
    {
        for(int j = 0; j < NUM_OF_COLUMNS; ++j)
        {
            std::cout << matrix.m_matrix[NUM_OF_COLUMNS*i + j].x      << ","
                      << matrix.m_matrix[NUM_OF_COLUMNS*i + j].y      << ","
                      << matrix.m_matrix[NUM_OF_COLUMNS*i + j].status << "  ";
        }
        std::cout << std::endl;
    }

	return a_os;
}


}//battle_ship namespace