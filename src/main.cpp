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
#include <ti/vars.h>
#include "complex_matrix.h"

using namespace ti::literals;  

int main(void)
{
    ComplexMatrix A = ComplexMatrix(OS_VAR_MAT_A);
    // A.Interchange(0, 1);
    // A.MultiplyRow(0, cplx_t{ti::real(), ti::real(1)});
    // A.DivideRow(0, cplx_t{ti::real(1), ti::real(1)});
    // A.CombineRows(0, 1, cplx_t{ti::real(), ti::real(1)});
    A.RREF();
    
    return 0;
}
