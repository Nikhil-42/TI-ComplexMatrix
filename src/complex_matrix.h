#include <ti/real>
#include <ti/vars.h>

class ComplexMatrix {
public:
    ComplexMatrix(const char *name);
    void Interchange(uint8_t row1, uint8_t row2);
    void MultiplyRow(uint8_t row, cplx_t multiplier);
    void DivideRow(uint8_t row, cplx_t divisor);
    void CombineRows(uint8_t targetRow, uint8_t sourceRow, cplx_t multiplier);
    
    void REF();
    void RREF();
private:
    matrix_t* data;
};