//============================================================================
// Name        : TSQRT.cpp
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
	GEQRT( A(0,0), T(0,0) );
}

void ExecKernel( TMatrix& A, TMatrix& T )
{
	for (int j=1; j<=TRIES; j++)
	{
		TSQRT( A(0,0), A(j,0), T(j,0) );
	}
}
