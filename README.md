FFTW_threading

A simple program to verify that the built-in threading in FFTW3 is working.

How to compile:
gcc -lfftw3_omp -lfftw3 -lm -fopenmp test_threaded.c

How to run:
export OMP_NUM_THREADS=NUMTHREADS

where NUMTHREADS is 8 or the number of threads you wish to utilize.

Timings with 1000 162x162x162 FFTs:

FFTW_ESTIMATE		
threads			time (s)		speedup
1			252			1.0
2			124			2.0
4			67			3.8
8			35			7.2
16			20			12.6
32			11			22.9
		
FFTW_MEASURE		
threads			time (s)		speedup
1			195			1.0
2			117			1.7
4			57			3.4
8			32			6.1
16			17			11.5
32			10			19.5
		
FFTW_PATIENT		
threads			time (s)		speedup
1			198			1
2			96			2
4			48			4
8			26			8
16			15			13
32			8			25
