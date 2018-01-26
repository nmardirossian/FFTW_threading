#include <omp.h>
#include <fftw3.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void main(){

    long int i,j;

    int howmany=1000;
    int dim1=162;
    int dim2=162;
    int dim3=162;
    long int dim=dim1*dim2*dim3;
    int rank=3;
    int n[]={dim1,dim2,dim3};
    long int idist=dim;
    int istride=2;
    const int *inembed=NULL;

    double finaltime;
    time_t initsec,finalsec;

    fftw_init_threads();
    fftw_plan_with_nthreads(omp_get_max_threads());

    fftw_complex *in=(fftw_complex*) fftw_malloc(sizeof(fftw_complex)*howmany*dim1*dim2*dim3);
    double *presumreal=(double*) fftw_malloc(sizeof(double)*howmany);
    double *presumcomp=(double*) fftw_malloc(sizeof(double)*howmany);
    double *postsumreal=(double*) fftw_malloc(sizeof(double)*howmany);
    double *postsumcomp=(double*) fftw_malloc(sizeof(double)*howmany);

    fftw_plan planfft = fftw_plan_many_dft(rank,n,howmany,in,inembed,istride,idist,in,inembed,istride,idist,FFTW_FORWARD,FFTW_PATIENT);
    fftw_plan planifft = fftw_plan_many_dft(rank,n,howmany,in,inembed,istride,idist,in,inembed,istride,idist,FFTW_BACKWARD,FFTW_PATIENT);

    for(i=0; i<howmany; i++){
        for(j=0; j<dim; j++){
            in[i*dim+j][0]=(double)j/((double)j+10.0);
            in[i*dim+j][1]=(double)j/((double)j+10.0);
        }
    }

    for(int i=0; i<howmany; i++){
        presumreal[i]=0.0;
        presumcomp[i]=0.0;
        postsumreal[i]=0.0;
        postsumcomp[i]=0.0;
    }

    for(i=0; i<howmany; i++){
        for(j=0; j<dim; j++){
            presumreal[i]=presumreal[i]+in[i*dim+j][0];
            presumcomp[i]=presumcomp[i]+in[i*dim+j][1];
        }
    }

    printf("Starting FFTs\n");
    initsec=time(NULL);
    fftw_execute(planfft);
    fftw_execute(planifft);
    finalsec=time(NULL);
    printf("Done with FFTs\n");
    finaltime=(double)(finalsec-initsec);
    printf("FFT and IFFT took %f seconds\n", finaltime);

    for(i=0; i<howmany; i++){
        for(j=0; j<dim; j++){
            postsumreal[i]=postsumreal[i]+in[i*dim+j][0];
            postsumcomp[i]=postsumcomp[i]+in[i*dim+j][1];
        }
    }

    for(i=0; i<howmany; i++){
        postsumreal[i]=postsumreal[i]/(double)dim;
        postsumcomp[i]=postsumcomp[i]/(double)dim;
    }

    for(i=0; i<howmany; i++){
        printf("presumreal %d: %16.12f\n",i,presumreal[i]);
        printf("presumcomp %d: %16.12f\n",i,presumcomp[i]);
        printf("postsumreal %d: %16.12f\n",i,postsumreal[i]);
        printf("postsumcomp %d: %16.12f\n",i,postsumcomp[i]);
    }

    fftw_destroy_plan(planfft);
    fftw_destroy_plan(planifft);
    fftw_free(in);
    fftw_cleanup_threads();
}
