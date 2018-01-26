FFTW_threading

A simple program to verify that the built-in threading in FFTW3 is working.

How to compile:
gcc -lfftw3_omp -lfftw3 -lm -fopenmp test_threaded.c

How to run:
export OMP_NUM_THREADS=NUMTHREADS

where NUMTHREADS is 8 or the number of threads you wish to utilize.
