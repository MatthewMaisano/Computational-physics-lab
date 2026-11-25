
/*******************************************************************************
*
* File main1.c
*
* Measurement of the processor time required to produce single-precision
* random numbers using ranlxs
*
* Author: Martin Luescher <luscher@mail.cern.ch>
*
*******************************************************************************/
#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "action.h"
#include "global.h"
#include "random.h"
#include "trajectory.h"
#include "correlatore.h"
#include "Energia.h"
#include "utility.h"
#include "var_init.h"
#include "print.h"
#include "jacknife.h"
#include "binning.h"

#define NLOOPS 100000


int main()
{
   /*inizializzo i cammini*/
   rlxd_init(1,time(0));
   gauss_dble(xx,N);
   ranlxd(r,N);
   ranlxd(rComp,N);

   /*faccio leggere al programma la dimensione su cui binnare ottenuta precedentemente*/
   int Dim_bin;
   FILE *autocorr_time;

   autocorr_time = fopen("Autocorrelation_time.txt", "r");

   if (fscanf(autocorr_time, "%d", &Dim_bin) != 1) 
   {
    fprintf(stderr, "Errore\n");
    fclose(autocorr_time);
    exit(1);
   }

   int Nsw = Nbin * Dim_bin;

   /*inzializzo array dinamici*/
   all_init();

   /*apro i File*/
   empty_global(xxBin[N]);
   
   /*compio Nsweep binnando nel mentre*/
   sweep(Nsw);

   /*stampo il risultato*/
   Print_Corr_Mediati();
   Print_Jack_Cluster();

   fclose(autocorr_time);
   return 0;
}


