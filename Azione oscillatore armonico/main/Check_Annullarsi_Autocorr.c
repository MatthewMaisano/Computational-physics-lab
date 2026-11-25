
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
   all_init();

   Read_jack_cluster();
   Read_Corr_Mediati();

   /*COMPLETO JACKNIFE*/
   double *sigma_jack = jack_end();
   
 
   Print_check(sigma_jack);
   
   free(Jack_Bin);
   free(sum);
   
   
   return 0;
}


