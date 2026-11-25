
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

#define NLOOPS 100000


int main()
{
   /*genero il primo cammino*/
   rlxd_init(1,time(0));
   gauss_dble(xx,N);
   ranlxd(r,N);
   ranlxd(rComp,N);

   /*inzializzo array dinamici*/
   all_init();

   /*scalo su tutti gli sweep*/
   sweep_di_prova();
 
   return 0;
}


