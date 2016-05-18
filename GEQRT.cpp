//============================================================================
// Name        : GEQRT.cpp
// Author      : T. Suzuki
// Version     :
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <omp.h>

#include <CoreBlasTile.hpp>
#include <TMatrix.hpp>

#include "KernelTuning.hpp"

using namespace std;

void SetTransMat( TMatrix& A, TMatrix& T )
{
}

void ExecKernel( TMatrix& A, TMatrix& T )
{
	for (int j=0; j<TRIES; j++)
	{
		GEQRT( A(j,j), T(j,j) );
	}
}
