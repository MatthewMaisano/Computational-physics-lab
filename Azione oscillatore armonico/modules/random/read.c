
/*******************************************************************************
*
* File ranlxs.c
*
* Reads a file with line separated numbers
* 
*******************************************************************************/

#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"


int read_file(){
   FILE *Data;
   Data = fopen("Data.txt","r");


   /*Conta righe file

   int numero = 1;
   char c;
   while((c=getc(Data)) != EOF)
      {
         if(c=='\n')
            numero++;
      }
   */

   /*Riempi array xx[i]*/
   for (int i=0; i<3; i++)
      {
         fscanf(Data, "%lf", &xx[i]);
      }
   fclose(Data);
   for (int i=0; i<3; i++)
   {
      printf("%lf \n", xx[i]);
   }
   return 0;
}

