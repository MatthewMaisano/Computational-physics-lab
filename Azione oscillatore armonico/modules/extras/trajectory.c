

#define TRAJECTORY_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "global.h"
#include "action.h"
#include "correlatore.h"
#include "jacknife.h"

#define PI 3.141592653589793


/*Funzione per generare una traiettoria con l'i-esima coordinata variata*/
void Newtrajectory() {
    for (int i = 0; i < N; i++) 
    {
        double x_old = xx[(i+N)%N];
        
        /* Genero lo spostamento casuale (shift) tra -DELTA e +DELTA */
        double shift = Deltax(i);
        double x_new = x_old + shift;
        
        /* Calcolo la variazione di azione */
        double ds = compute_DeltaS(i, x_old, x_new);
        
        /* Test di Metropolis*/
        if (rComp[i] < exp(-ds)) {
            xx[i] = x_new;
        }
    }
}     
void sweep_di_prova()
{
   FILE *action_val;
   action_val=fopen("Action_check_therm.txt", "w");
   fprintf(action_val, "%lf\n", action());


   /*PROVA PER VEDERE LA DISTRIBUZIONE*/
   FILE *X1;
   X1=fopen("Distrib_x1.txt", "w");
   fprintf(X1, "%lf\n", xx[0]);

   for (int i=0; i<SweepInit + therm  ;i++)
   {  
      ranlxd(r,N);
      ranlxd(rComp,N);

      /*creo nuova configurazione con algoritmo Montecarlo*/
      Newtrajectory();

      fprintf(action_val, "%lf\n", action());
      
      /*scarto i primi therm sweep*/
      if(i >= therm)
      {
         fill_corr_tmarkov(i-therm);
      }
      fprintf(X1, "%lf\n", xx[0]);
   }
   Print_autocorr();
}

void sweep(int Nsw)
{
   int bin_index = 0;

   int Dim_bin = Nsw/Nbin;

   
   

   for (int i=0; i<Nsw +therm  ;i++)
   {  
      ranlxd(r,N);
      ranlxd(rComp,N);

      /*creo nuova configurazione con algoritmo Montecarlo*/
      /*xxNew();*/
      Newtrajectory(); 
      if(i >= therm)
      {
         /*riempio correlatore per un cammino al tempo FISICO t e scalo su tutti i t,
         intanto sommo per trovare i correlatori medi*/              
         fill_correlator();

         /*fill_corr_tmarkov(i);*/
         bin_index = fill_bin(bin_index, i - therm, Dim_bin);
      }  
   }
}

