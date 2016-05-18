//============================================================================
// Name        : KernelTuning.hpp
// Author      : T. Suzuki
// Version     :
//============================================================================

#define MAX_DIVS 100
#define TRIES 5

void SetTransMat( TMatrix& A, TMatrix& T );
void ExecKernel( TMatrix& A, TMatrix& T );
