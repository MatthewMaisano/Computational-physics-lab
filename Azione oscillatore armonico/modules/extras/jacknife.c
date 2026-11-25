#define JACKNIFE

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "global.h"
#include "trajectory.h"
#include "utility.h"
#include "correlatore.h"

#define PI 3.141592653589793

double sigmaJack(double **Jack_Bin, int j)
{
   /*calcolo la media*/
   double media = 0;
   for (int i = 0; i < Nbin; i++)
   {
      media += Jack_Bin[i][j];
   }

   /*calcolo la sigma*/
   double sigma = 0;
   for (int i = 0; i < Nbin; i++)
   {
      sigma += ((Nbin - 1.)/Nbin) * pow(Jack_Bin[i][j] - (media/Nbin), 2);
   }
   return sigma;
}

double *jack_end()
{

	for (int i = 0; i < Nbin; i++)
   	{
      	for (int j = 0; j < N-1 ; j++)
      	{
         	Jack_Bin[i][j] += xxBin[j];
      	}
   	}

   	/*divido tutte le entrate per Nbin - 1 */
   	for (int i = 0; i < Nbin; i++)
   	{
      	for (int j = 0; j < N-1 ; j++)
      	{
         	Jack_Bin[i][j] /= (Nbin - 1.);
      	}
   	}

   	/*calcolo la sigma sui correlatori binnati con jacknife*/
   	double *sigma_jack = (double*)malloc((N-1)*sizeof(double));
   	for (int j=0; j < N - 1; j++)
   	{
      	sigma_jack[j] = sigmaJack(Jack_Bin, j);
   	}
   	return sigma_jack;
}



int fill_bin(int bin_index, int i, int Dim_bin)
{
	if((i+1)%Dim_bin==0)
    {
       	/*sommo i vari Bin*/
        for (int j=0 ;j< N ;j++)
        {
                                                /*DIVIDO IN DUE PARTI: CORRELATOR CALC E JACK 1ST PART*/
            double diff = (corr[j]-D[j])/Dim_bin;
            xxBin[j] += diff;
    		xxBinQuad[j] += pow(diff,2);

            /*calcolo cluster Jacknife*/
			/*sommo su tutti i bin ad ogni cambio di bin*/
    		sum[j] = xxBin[j];

    		/*riempio Jack_Bin con il valore del bin corrispondente (*-Nbin) */  
    		Jack_Bin[bin_index][j] = -diff;
    		D[j] = corr[j];
        }
        bin_index += 1;
    }
    return bin_index;
}
