#include "matrix.h"
#include "cplx_t.h"

/*
 * =============================================================================================
 * Matrix
 * =============================================================================================
 */

Matrix::Matrix(uint8_t rows, uint8_t columns) : m_rows(rows), m_columns(columns)
{
    m_data = new cplx_t[rows * columns];
}

const cplx_t &Matrix::at(uint8_t row, uint8_t column) const
{
    return *(m_data + row * m_columns + column);
}

cplx_t &Matrix::at(uint8_t row, uint8_t column)
{
    return *(m_data + row * m_columns + column);
}

Matrix::Row Matrix::operator[](uint8_t row)
{
    return Row(*this, row);
}

void Matrix::ref()
{
    for (uint8_t i = 0; i < m_rows; i++)
    {
        Row row = (*this)[i];
        if (row[0] == cplx_t{})
        {
            for (uint8_t j = i + 1; j < m_rows; j++)
            {
                // if ((*this)[j][0] != cplx_t{os_Int24ToReal(0), os_Int24ToReal(0)})
                // {
                //     Row other = (*this)[j];
                //     row.swap(other);
                //     break;
                // }
            }
        }
    }
}

/*
 * =============================================================================================
 * Matrix::Row
 * =============================================================================================
 */

const cplx_t &Matrix::Row::at(uint8_t column) const
{
    return m_parent.at(m_row, column);
}

cplx_t &Matrix::Row::at(uint8_t column)
{
    return m_parent.at(m_row, column);
}

Matrix::Row &Matrix::Row::combine(const cplx_t &scalar, const Matrix::Row &other)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
    {
        at(i) += scalar * other.at(i);
    }
    return *this;
}

Matrix::Row &Matrix::Row::swap(Matrix::Row &other)
{
    cplx_t temp;
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
    {
        temp = at(i);
        at(i) = other.at(i);
        other.at(i) = temp;
    }
    return *this;
}

const cplx_t &Matrix::Row::operator[](uint8_t column) const
{
    return at(column);
}

cplx_t &Matrix::Row::operator[](uint8_t column)
{
    return at(column);
}

Matrix::Row &Matrix::Row::operator+=(const cplx_t &scalar)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
        at(i) += scalar;
    return *this;
}

Matrix::Row &Matrix::Row::operator-=(const cplx_t &scalar)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
        at(i) -= scalar;
    return *this;
}

Matrix::Row &Matrix::Row::operator*=(const cplx_t &scalar)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
        at(i) *= scalar;
    return *this;
}

Matrix::Row &Matrix::Row::operator/=(const cplx_t &scalar)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
        at(i) /= scalar;
    return *this;
}

Matrix::Row &Matrix::Row::operator+=(const Row &other)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
        at(i) += other.at(i);
    return *this;
}

Matrix::Row &Matrix::Row::operator-=(const Row &other)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
        at(i) -= other.at(i);
    return *this;
}

Matrix::Row &Matrix::Row::operator*=(const Row &other)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
        at(i) *= other.at(i);
    return *this;
}

Matrix::Row &Matrix::Row::operator/=(const Row &other)
{
    for (uint8_t i = 0; i < m_parent.m_columns; i++)
        at(i) /= other.at(i);
    return *this;
}