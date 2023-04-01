#include <ti/real>
#include <ti/vars.h>

class ComplexMatrix {
public:
    ComplexMatrix(const char *name);
    ComplexMatrix(matrix_t *data);
    ComplexMatrix(const ComplexMatrix &other);

    ComplexMatrix& Interchange(uint8_t row1, uint8_t row2);
    ComplexMatrix& MultiplyRow(uint8_t row, cplx_t multiplier);
    ComplexMatrix& DivideRow(uint8_t row, cplx_t divisor);
    ComplexMatrix& CombineRows(uint8_t targetRow, uint8_t sourceRow, cplx_t multiplier);
    
    ComplexMatrix& REF();
    ComplexMatrix& RREF();

    matrix_t* GetData();

    ComplexMatrix& operator=(const ComplexMatrix &other);
    ~ComplexMatrix();

    static void Copy(const ComplexMatrix& from, ComplexMatrix& to);
private:
    matrix_t* data;
    bool cleanup;
};