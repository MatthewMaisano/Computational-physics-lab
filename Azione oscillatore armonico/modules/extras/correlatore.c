

#define CORRELATORE_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "global.h"
#include "action.h"
#include "jacknife.h"

#define PI 3.141592653589793

/*Funzione che calcola il correlatore per lo sweep corrente*/
double correlator(int t)
{
   double corr = 0;
   double correlator = 0;
   for (int i=0; i<N ; i++)
   {
      correlator += (xx[(i + N)%N]*xx[(i+t+N)%N]);
   }
   corr = correlator/N;
   return corr;
}

double autocorrelator(int t,int k)
{
   double autocorr = 0;
   double autocorrelator1 = 0;
   double autocorrelator2 = 0;
   for (int i=0; i<SweepInit-t ; i++)
   {
      autocorrelator1 += CorrtMarkov[i][k]*CorrtMarkov[i+t][k];
      autocorrelator2 += CorrtMarkov[i][k];
   }
   autocorr = (autocorrelator1/(SweepInit-t)) - (pow(autocorrelator2,2)/((SweepInit-t)*(SweepInit-t)));
   return autocorr;
}

void fill_correlator()
{
   for (int t=0; t<N ;t++)
      {
         corr[t] += correlator(t);
         corrQuad[t] += correlator(t)*correlator(t);
      }
}

void fill_corr_tmarkov(int i)
{
   for(int t = 1; t<N; t++)
      {
         CorrtMarkov[i][t-1] = correlator(t);
      }
}   



