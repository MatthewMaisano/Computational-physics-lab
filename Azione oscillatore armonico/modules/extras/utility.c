#define UTILITY_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "global.h"
#include "trajectory.h"

#define PI 3.141592653589793

void empty_array(double *array)
	{
		
		for (int i=0; i<N; i++)
   		{
      		array[i] = 0;
   		}
	}

void empty_matrix(double **matrix)
	{

		for (int i=0; i<Nbin; i++)
		{
				for (int j=0; j<N; j++)
				{
      				matrix[i][j] = 0;
   				}
		}
	}
void empty_global(double array[])
{
	for (int i =0; i<sizeof(array)/sizeof(array[0]) -1; i++)
	{
		array[i] = 0;
	}
}
