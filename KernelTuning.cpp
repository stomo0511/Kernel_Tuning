//============================================================================
// Name        : KernelTuning.cpp
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

int main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		cerr << "Usage: a.out [natural number]\n";
		return EXIT_FAILURE;
	}

	int nb = atoi(argv[1]);
	int count = 0;
	int ibs[MAX_DIVS];

	// Sieve of Eratosthenes
	for (int i=1; i<=nb; i++)
	{
		if ( nb % i == 0 )
		{
			ibs[count] = i;
			count++;
		}
	}

	#ifdef DEBUG
	cout << "Max threads = " << omp_get_max_threads() << endl;
	cout << "Timer precision = " << omp_get_wtick() << endl;
	cout << "NB = " << nb << " : ";
	for (unsigned int i=0; i<count; i++)
		cout << ibs[i] << ", ";
	cout << endl;
	#endif

	/////////////////////////////////////////
	double time;

	for (int i = 0; i<count; i++)
	{
		if ((ibs[i] >= 10) && (ibs[i] != nb))
		{
			cout << nb << ", " << ibs[i] << ", " << flush;

			TMatrix A( (TRIES+1)*nb, (TRIES+1)*nb, nb, nb, ibs[i]);
			TMatrix T( (TRIES+1)*ibs[i], (TRIES+1)*nb, ibs[i], nb, ibs[i]);

			A.Set_Rnd( 20160511 );

			SetTransMat( A, T );

			// Timer start
			time = omp_get_wtime();

			ExecKernel( A, T );

			// Timer stop
			time = omp_get_wtime() - time;
			time /= TRIES;
			cout << time << endl;

//			A.~TMatrix();
//			T.~TMatrix();
		}
		// if (ibs[i] >= 0) END
	}
	// i-loop END

	return EXIT_SUCCESS;
}
