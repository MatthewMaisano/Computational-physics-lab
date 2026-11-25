
/*******************************************************************************
*
* File gauss.c
* 
* Generation of Gaussian random numbers
*
* The externally accessible functions are
*
*   void gauss(float r[],int n)
*     Generates n single-precision Gaussian random numbers x with distribution
*     proportional to exp(-x^2) and assigns them to r[0],..,r[n-1]
*
*   void gauss_dble(double rd[],int n)
*     Generates n double-precision Gaussian random numbers x with distribution
*     proportional to exp(-x^2) and assigns them to rd[0],..,rd[n-1]
*
* Version 1.0
* Author: Martin Luescher <luscher@mail.cern.ch>
*
*******************************************************************************/

#define ACTION_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "global.h"
#include "trajectory.h"

#define PI 3.141592653589793


double action()
{
   double Action = 0.;
   double M = m/a;
   double Omeg = w*a;
   for(int i=0; i<N; i++)
   {
      Action += (0.5*M*pow((xx[(i+1+N)%N]-xx[(i + N)%N]),2) + 0.5*M*(Omeg*Omeg)*pow(xx[(i + N)%N],2));
   }
   return Action;
}
double actionprov(double x[])
{
   double S = 0;
   double M = m/a;
   double Omeg = w*a;
   for(int i=0; i<N+1; i++)
   {
      S = S + (0.5*M*pow((x[(i+1+N)%N]-x[(i + N)%N]),2) + 0.5*M*(Omeg*Omeg)*pow(x[(i+ N)%N],2));
   }
   return S;
}
double Deltax(int i)
{
   double deltax = 2*DELTA*(r[i]-0.5);
   return deltax;
}

/* Calcola la variazione di azione locale*/
double compute_DeltaS(int i, double x_old, double x_new) 
{
    double x_next = xx[(i + 1) % N];     
    double x_prev = xx[(i - 1 + N) % N];  
    
    double kappa = a * a * w * w + 2.0;
    
    return (m / (2.0 * a)) * (x_new - x_old) * (kappa * (x_new + x_old) - 2.0 * x_next - 2.0 * x_prev);
}
      

