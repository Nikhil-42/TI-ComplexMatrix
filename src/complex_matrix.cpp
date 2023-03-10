#include "complex_matrix.h"
#include <fileioc.h>

#define IN_RANGE(num, low, high) (low <= num && num < high)
#define VALID_INDEX(i, size) IN_RANGE(i, 0, size)

ComplexMatrix::ComplexMatrix(const char *name) {
    ti_RclVar(OS_TYPE_MATRIX, name, (void**) &data);
};

void ComplexMatrix::Interchange(uint8_t row1, uint8_t row2) {
    if (VALID_INDEX(row1, data->rows) && VALID_INDEX(row2, data->rows)) {
        ti::real temp;
        for (uint8_t col = 0; col < data->cols; col++) {
            temp = OS_MATRIX_ELEMENT(data, row1, col);
            OS_MATRIX_ELEMENT(data, row1, col) = OS_MATRIX_ELEMENT(data, row2, col);
            OS_MATRIX_ELEMENT(data, row2, col) = temp;
        }
    }
}

void ComplexMatrix::MultiplyRow(uint8_t row, cplx_t multiplier) {
    if (VALID_INDEX(row, data->rows)) {
        ti::real real, imag;
        for (uint8_t col = 0; col < data->cols; col+=2) {
            real = OS_MATRIX_ELEMENT(data, row, col);
            imag = OS_MATRIX_ELEMENT(data, row, col + 1);

            OS_MATRIX_ELEMENT(data, row, col) = real * multiplier.real - imag * multiplier.imag;
            OS_MATRIX_ELEMENT(data, row, col + 1) = imag * multiplier.real + real * multiplier.imag;
        }
    }
}

void ComplexMatrix::DivideRow(uint8_t row, cplx_t divisor) {
    ti::real realDivisor = ti::real(divisor.real) * divisor.real + ti::real(divisor.imag) * divisor.imag;
    MultiplyRow(row, cplx_t{ti::real(divisor.real) / realDivisor, -ti::real(divisor.imag) / realDivisor});
}

void ComplexMatrix::CombineRows(uint8_t targetRow, uint8_t sourceRow, cplx_t multiplier) {
    if (VALID_INDEX(targetRow, data->rows) && VALID_INDEX(sourceRow, data->rows)) {
        ti::real targetReal, targetImag;
        ti::real sourceReal, sourceImag;

        for (uint8_t col = 0; col < data->cols; col+=2) {
            targetReal = OS_MATRIX_ELEMENT(data, targetRow, col);
            targetImag = OS_MATRIX_ELEMENT(data, targetRow, col + 1);
            sourceReal = OS_MATRIX_ELEMENT(data, sourceRow, col);
            sourceImag = OS_MATRIX_ELEMENT(data, sourceRow, col + 1);
            
            OS_MATRIX_ELEMENT(data, targetRow, col) = 
                targetReal + (sourceReal * multiplier.real - sourceImag * multiplier.imag);
            OS_MATRIX_ELEMENT(data, targetRow, col + 1) =
                targetImag + (sourceImag * multiplier.real + sourceReal * multiplier.imag);
        }
    }
}

void ComplexMatrix::RREF() {
    uint8_t row = 0, col = 0;
    while (col < data->cols && row < data->rows) {

        // If the pivot element is zero 
        if (ti::real() == OS_MATRIX_ELEMENT(data, row, col) && ti::real() == OS_MATRIX_ELEMENT(data, row, col + 1)) {
            // Search the column for a non zero pivot
            uint8_t nonZeroRow = row + 1;
            for (; nonZeroRow < data->rows; nonZeroRow++) {
                // If one is found interchange the rows
                if (ti::real() != OS_MATRIX_ELEMENT(data, nonZeroRow, col) || ti::real() != OS_MATRIX_ELEMENT(data, nonZeroRow, col + 1)) {
                    Interchange(row, nonZeroRow);
                }
            }
            // Otherwise
            if (nonZeroRow == data->rows) col+=2; break;
        }

        DivideRow(row, cplx_t{OS_MATRIX_ELEMENT(data, row, col), OS_MATRIX_ELEMENT(data, row, col + 1)});
        for (uint8_t otherRow = 0; otherRow < data->rows; otherRow++) {
            if (otherRow == row) continue;
            CombineRows(otherRow, row, cplx_t{-ti::real(OS_MATRIX_ELEMENT(data, otherRow, col)), -ti::real(OS_MATRIX_ELEMENT(data, otherRow, col + 1))});
        }

        row++;
        col+=2;
    }
}

void ComplexMatrix::REF() {
    RREF();
}