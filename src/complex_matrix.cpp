#include "complex_matrix.h"
#include "cplx"
#include <fileioc.h>

#define IN_RANGE(num, low, high) (low <= num && num < high)
#define VALID_INDEX(i, size) IN_RANGE(i, 0, size)
#define CPLX_MATRIX_ELEMENT(data, row, col) (*((cplx_t*) &OS_MATRIX_ELEMENT(data, row, 2*col)))

/**
 * Returns a complex matrix representation of the given matrix.
*/
ComplexMatrix::ComplexMatrix(const char *name) {
    cleanup = false;
    ti_RclVar(OS_TYPE_MATRIX, name, (void**) &data);
};

ComplexMatrix::ComplexMatrix(matrix_t *data) : data(data), cleanup(false) {};

/**
 * Returns a copy of the given complex matrix.
*/
ComplexMatrix::ComplexMatrix(const ComplexMatrix &other) {
    cleanup = true;
    data = ti_MallocMatrix((size_t) other.data->rows, (size_t) other.data->cols);
    Copy(other, *this);
}

ComplexMatrix& ComplexMatrix::Interchange(uint8_t row1, uint8_t row2) {
    if (VALID_INDEX(row1, data->rows) && VALID_INDEX(row2, data->rows)) {
        ti::cplx temp;
        for (uint8_t col = 0; col < data->cols/2; col++) {
            temp = CPLX_MATRIX_ELEMENT(data, row1, col);
            CPLX_MATRIX_ELEMENT(data, row1, col) = CPLX_MATRIX_ELEMENT(data, row2, col);
            CPLX_MATRIX_ELEMENT(data, row2, col) = temp;
        }
    }
    return *this;
}

ComplexMatrix& ComplexMatrix::MultiplyRow(uint8_t row, cplx_t multiplier) {
    if (VALID_INDEX(row, data->rows)) {
        ti::cplx elem;
        for (uint8_t col = 0; col < data->cols/2; col++) {
            elem = CPLX_MATRIX_ELEMENT(data, row, col);
            CPLX_MATRIX_ELEMENT(data, row, col) = elem * multiplier;
        }
    }
    return *this;
}

ComplexMatrix& ComplexMatrix::DivideRow(uint8_t row, cplx_t divisor) {
    if (VALID_INDEX(row, data->rows)) {
        ti::cplx elem;
        for (uint8_t col = 0; col < data->cols/2; col++) {
            elem = CPLX_MATRIX_ELEMENT(data, row, col);
            CPLX_MATRIX_ELEMENT(data, row, col) = elem / divisor;
        }
    }
    
    return *this;
}

ComplexMatrix& ComplexMatrix::CombineRows(uint8_t targetRow, uint8_t sourceRow, cplx_t multiplier) {
    if (VALID_INDEX(targetRow, data->rows) && VALID_INDEX(sourceRow, data->rows)) {
        for (uint8_t col = 0; col < data->cols/2; col++) {
            ti::cplx(CPLX_MATRIX_ELEMENT(data, targetRow, col)) += ti::cplx(CPLX_MATRIX_ELEMENT(data, sourceRow, col)) * multiplier;
        }
    }
    return *this;
}

ComplexMatrix& ComplexMatrix::RREF() {
    uint8_t row = 0, col = 0;
    while (col < data->cols/2 && row < data->rows) {

        // If the pivot element is zero 
        if (ti::cplx() == CPLX_MATRIX_ELEMENT(data, row, col)) {
            // Search the column for a non zero pivot
            uint8_t nonZeroRow = row + 1;
            for (; nonZeroRow < data->rows; nonZeroRow++) {
                // If one is found interchange the rows
                if (ti::cplx() != CPLX_MATRIX_ELEMENT(data, nonZeroRow, col)) {
                    Interchange(row, nonZeroRow);
                }
            }

            // Otherwise
            if (nonZeroRow == data->rows) col++; break;
        }

        DivideRow(row, CPLX_MATRIX_ELEMENT(data, row, col));
        for (uint8_t otherRow = 0; otherRow < data->rows; otherRow++) {
            if (otherRow == row) continue;
            CombineRows(otherRow, row, -ti::cplx(CPLX_MATRIX_ELEMENT(data, otherRow, col)));
        }

        row++;
        col++;
    }
    return *this;
}

ComplexMatrix& ComplexMatrix::REF() {
    uint8_t row = 0, col = 0;
    while (col < data->cols/2 && row < data->rows) {

        // If the pivot element is zero 
        if (ti::cplx() == CPLX_MATRIX_ELEMENT(data, row, col)) {
            // Search the column for a non zero pivot
            uint8_t nonZeroRow = row + 1;
            for (; nonZeroRow < data->rows; nonZeroRow++) {
                // If one is found interchange the rows
                if (ti::cplx() != CPLX_MATRIX_ELEMENT(data, nonZeroRow, col)) {
                    Interchange(row, nonZeroRow);
                }
            }

            // Otherwise
            if (nonZeroRow == data->rows) col++; break;
        }

        for (uint8_t otherRow = row + 1; otherRow < data->rows; otherRow++) {
            CombineRows(otherRow, row, -ti::cplx(CPLX_MATRIX_ELEMENT(data, otherRow, col)) / CPLX_MATRIX_ELEMENT(data, row, col));
        }

        row++;
        col++;
    }
    return *this;
}

matrix_t* ComplexMatrix::GetData() {
    return data;
}

ComplexMatrix& ComplexMatrix::operator=(const ComplexMatrix &other) {
    if (cleanup) {
        free(data);
    }

    cleanup = true;
    data = ti_MallocMatrix((size_t) other.data->rows, (size_t) other.data->cols);
    Copy(other, *this);
    return *this;
}

ComplexMatrix::~ComplexMatrix() {
    if (cleanup) {
        free(data);
    }
}

void ComplexMatrix::Copy(const ComplexMatrix& from, ComplexMatrix& to) {
#define __min(a,b) (((a) < (b)) ? (a) : (b))
    uint8_t rows = __min(from.data->rows, to.data->rows);
    uint8_t cols = __min(from.data->cols, to.data->cols);
#undef __min
    for (uint8_t row = 0; row < rows; row++) {
        for (uint8_t col = 0; col < cols; col++) {
            OS_MATRIX_ELEMENT(to.data, row, col) = OS_MATRIX_ELEMENT(from.data, row, col);
        }
    }
}