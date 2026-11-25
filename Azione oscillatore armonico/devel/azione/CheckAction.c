#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "random.h"
#include "global.h"
#include "action.h"

#define PI 3.141592653589793
/*In questo check l'azione viene calcolata su una serie di dati, generati ad hoc per renderla nulla
la ciclicità è un problema, perchè per colpa di questa, l'azione calcolata su x[0]-x[N] sarà non nulla.
per ovviare a questo problema calcolo solo il valore dell'azione sul tratto x[0] - x[N] e dico che
l'azione totale deve essere uguale all'azione su questo tratto (tutti gli altri danno contributo 0)*/

int main()
{
   /* Creo l'array che mi annulla l'azione*/
   double x[N];
   double seed = PI;
   x[0] = seed;
   for (int i=0; i<N; i++)
      {
         x[i+1] = x[i]*(1+sqrt(w/m)); 
      }

   /*calcolo quanto vale l'azione sul tratto x[0] - x[N]*/
   double M = m/a;
   double Omeg = w*a;
   double delta = (0.5*M*pow((x[0]-x[N]),2) + 0.5*M*(Omeg*Omeg)*pow(x[N],2));
   
   /*check azione*/
   double Sprov = actionprov(x) + delta ;
   /*if (Sprov == delta)
   {
      printf("L'azione è corretta\n");
   }
   else
   {
      printf("l'azione non è corretta\n");
   }*/
   printf("%lf \n", actionprov(x));
   return 0;
}
