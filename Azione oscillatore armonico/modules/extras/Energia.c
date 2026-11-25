

#define ENERGIA_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "global.h"
#include "action.h"

#define PI 3.141592653589793

/*funzione che calcola l'energia su uno sweep* (vettore a N-2 entrate)*/
void Energy()
{
   for(int t = 1; t<N-2; t++)
   {
      E[t - 1] = acosh(((xxBin[t+1]) + (xxBin[t-1]))/ (2*xxBin[t]))/a;
   }
}

/*energia per jacknife*/
void Energy_Jack(double **jack, double **E)
{
   for(int j = 0; j < Nbin; j++)
   {
      for(int t = 1; t<N-2; t++)
      {
         E[j][t-1] = acosh(((jack[j][t+1]) + (jack[j][t-1]))/ (2*jack[j][t]))/a;
      }
   }   
}

void printEnergy()
{
   FILE *Energy;
   Energy=fopen("Energy.txt", "w");
   for (int t=0; t<N-2; t++)
   {
      fprintf(Energy, "%lf \n", E[t]);
   }
}
void print_t()
{
   FILE *temp;
   temp=fopen("tempo_fisico.txt", "w");
   for(int t = 0; t<N-2; t++)
   {
      fprintf(temp,"%d \n", t+1);
   }
}
void Elemento_matr()
{
   /*int Dim_bin;
   FILE *autocorr_time;

   autocorr_time = fopen("Autocorrelation_time.txt", "r");
   fscanf(autocorr_time, "%d", &Dim_bin);

   int Nbin = (Nsweep-(Nsweep%Dim_bin))/Dim_bin;*/
   for(int t = 1; t<N-1; t++)
   {
      Matr[t - 1] = ((xxBin[t]/Nbin)*exp(0.5 * N *a* E[t - 1] ) )/(2 * cosh(((0.5 * N) - t)*a*E[t - 1]));
   }
}

void Elemento_matr_Jack(double **jack, double **E, double **Matr)
{
   for(int j = 0; j < Nbin; j++)
   {
      for(int t = 1; t<N-1; t++)
      {
         Matr[j][t-1] = (jack[j][t]*exp(0.5 * N  * a * E[j][t-1] ) )/(2 * cosh(((0.5 * N) - t) * a* E[j][t-1]));
      }
   }
}

void printMatr()
{
   FILE *Matrix;
   Matrix=fopen("Matrix.txt", "w");
   for (int t=0; t<N-2; t++)
   {
      fprintf(Matrix, "%lf \n", Matr[t]);
   }
}




      

