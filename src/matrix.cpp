#include "../inc/matrix.hpp"

namespace battle_ship
{

namespace impl
{
     
void reset_buffer(int* buffer)
{
    for (int i = 0; i < NUM_OF_POINTS; ++i)
        buffer[i] = 0;
}

int get_index(int x, int y)
{
    return NUM_OF_COLUMNS*x + y;
}

int is_index_inside_matrix_range(int index)
{
    if(index >= NUM_OF_POINTS || index < 0)
        return false;
    return true;
}


}//impl namespace

Matrix::Matrix()
{
    impl::reset_buffer(m_matrix);
}

int Matrix::get(int x, int y)
{
    int index = impl::get_index(x, y);
    assert(impl::is_index_inside_matrix_range(index));
    return m_matrix[index];
}

void Matrix::set(int x, int y, int value)
{
    int index = impl::get_index(x, y);
    assert(impl::is_index_inside_matrix_range(index));
    m_matrix[index] = value;
}

std::ostream& operator<<(std::ostream& a_os, Matrix const& matrix)
{
    for(int i = 0; i < NUM_OF_COLUMNS; ++i)
    {
        for(int j = 0; j < NUM_OF_COLUMNS; ++j)
            std::cout << matrix.m_matrix[NUM_OF_COLUMNS*i + j] << " ";
        std::cout << std::endl;
    }

	return a_os;
}


}//battle_ship namespace