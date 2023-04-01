/*
 *--------------------------------------
 * Program Name: Complex Matricies
 * Author: Nikhil Iyer
 * License: MIT
 * Description: This program implement complex matricies on the CE
 *--------------------------------------
*/
#include <stdint.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/real>
#include <ti/ui.h>
#include <ti/vars.h>
#include <ti/tokens.h>
#include "complex_matrix.h"

using namespace ti::literals;  

int main(void)
{
    os_RunIndicOn();
    ComplexMatrix A{OS_VAR_MAT_A};
    ComplexMatrix A_SAVE{A};
    A.RREF();

    os_SetMatrixDims(OS_VAR_MAT_B, A.GetData()->rows, A.GetData()->cols);
    ComplexMatrix B{OS_VAR_MAT_B};
    ComplexMatrix::Copy(A, B);
    
    ComplexMatrix::Copy(A_SAVE, A);

    os_RunIndicOff();
    
    return 0;
}
