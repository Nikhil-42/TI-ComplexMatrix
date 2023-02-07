#include <ti/real>

using namespace ti::literals;

class Matrix
{
private:
    cplx_t* m_data;
    uint8_t m_rows, m_columns;
public:
    class Row {
    private:
        Matrix& m_parent;
        uint8_t m_row;

        friend class Matrix;
        Row(Matrix& parent, uint8_t row): m_parent(parent), m_row(row) {};
    public:
        Row& combine(const cplx_t& scalar, const Row& other);
        Row& swap(Row& other);

        const cplx_t& at(uint8_t column) const;
        cplx_t& at(uint8_t column);

        const cplx_t& operator[](uint8_t column) const;
        cplx_t& operator[](uint8_t column);

        Row& operator+=(const cplx_t& scalar);
        Row& operator-=(const cplx_t& scalar);
        Row& operator*=(const cplx_t& scalar);
        Row& operator/=(const cplx_t& scalar);

        Row& operator+=(const Row& other);
        Row& operator-=(const Row& other);
        Row& operator*=(const Row& other);
        Row& operator/=(const Row& other);
    };
    
public:
    /// @brief Create a new Matrix with the given number of rows and columns.
    /// @param rows the number of rows this matrix should have
    /// @param columns the number of columns this matrix should have
    Matrix(uint8_t rows, uint8_t columns);

    const cplx_t& at(uint8_t row, uint8_t column) const;
    cplx_t& at(uint8_t row, uint8_t column);

    /// @brief Returns a accessor to the row at the given index.
    /// @param row the row to access
    /// @return a reference to the row at the given index
    Row operator[](uint8_t row);
    
    /// @brief Reduces this matrix into row echelon form.
    void ref(); 

    /// @brief Further reduces this matrix into reduced row echelon form.
    void rref();

    /// @brief Deallocates the memory owned by this matrix.
    ~Matrix();
};
