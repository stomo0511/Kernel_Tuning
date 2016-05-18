//============================================================================
// Name        : SSRFB.cpp
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
	TSQRT( A(0,0), A(1,0), T(1,0) );

//    #pragma omp parallel for
	for (int j=1; j<=TRIES; j++)
	{
		LARFB( PlasmaLeft, PlasmaTrans, A(0,0), T(0,0), A(0,j) );
	}
}

void ExecKernel( TMatrix& A, TMatrix& T )
{
	for (int j=1; j<=TRIES; j++)
	{
		SSRFB( PlasmaLeft, PlasmaTrans, A(1,0), T(1,0), A(0,j), A(1,j) );
	}
}
