#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include "random.h"
#include "global.h"
#include "action.h"

#define PI 3.141592653589793


int main()
{
   gauss_dble(xx,N);
   double VarS[N];
   for (int i=0; i<N; i++)
   {
      VarS[i] = DeltaS(i);
      printf("%lf \n", VarS[i]);
   }
   return 0;
}

