#define VAR_INIT_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "global.h"
#include "trajectory.h"
#include "utility.h"

#define PI 3.141592653589793


double matrix_init()
{
	double **matrix;
  	matrix = (double**) malloc(Nbin * sizeof(double));

   	for (int i=0 ;i<Nbin ;i++)
      matrix[i]=(double*)malloc(N*sizeof(double)); 

  	return **matrix;
}

double vec_init()
{
	double *vec = (double*)malloc(N*sizeof(double));

	return *vec;
}

void all_init()
{
	sum = (double*)malloc(N*sizeof(double));
	empty_array(sum);

	Matr_Jack = (double**) malloc(Nbin * sizeof(double));
	for (int i=0 ;i<Nbin ;i++)
    	Matr_Jack[i]=(double*)malloc(N*sizeof(double)); 
    empty_matrix(Matr_Jack);

    E_Jack = (double**) malloc(Nbin * sizeof(double));
	for (int i=0 ;i<Nbin ;i++)
    	E_Jack[i]=(double*)malloc(N*sizeof(double)); 
    empty_matrix(E_Jack);

    Jack_Bin = (double**) malloc(Nbin * sizeof(double));
	for (int i=0 ;i<Nbin ;i++)
    	Jack_Bin[i]=(double*)malloc(N*sizeof(double)); 
    empty_matrix(Jack_Bin);

    xxBinQuad = (double*)malloc(N*sizeof(double));
	empty_array(xxBinQuad);

	corr = (double*)malloc(N*sizeof(double));
	empty_array(corr);

	D = (double*)malloc(N*sizeof(double));
	empty_array(D);

	corrQuad = (double*)malloc(N*sizeof(double));
	empty_array(corrQuad);
}

