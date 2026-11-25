
/*******************************************************************************
*
* File ym1.c
*
* Copyright (C) 2010-2013 Martin Luescher
*
* This software is distributed under the terms of the GNU General Public
* License (GPL)
*
* HMC simulation program for the SU(3) gauge theory.
*
* Syntax: ym1 -i <filename> [-noloc] [-noexp] [-rmold] [-noms]
*                           [-c <filename> [-a [-norng]]]
*
* For usage instructions see the file README.ym1.
*
*******************************************************************************/

#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/*#include "flags.h"
#include "random.h"
#include "su3fcts.h"
#include "utils.h"
#include "lattice.h"
#include "uflds.h"
#include "archive.h"*/
#include "forces.h"
#include "update.h"
#include "wflow.h"
#include "tcharge.h"
#include "version.h"
#include "global.h"

#define N0 (NPROC0*L0)
#define N1 (NPROC1*L1)
#define N2 (NPROC2*L2)
#define N3 (NPROC3*L3)

typedef struct
{
   int nt,iac;
   double dH,avpl;
} dat_t;

static struct
{
   int dn,nn,tmax;
   double eps;
} file_head;

static struct
{
   int nt;
   double **Wsl,**Ysl,**Qsl;
} data;

/*static int my_rank,noloc,noexp,rmold,noms,norng;
static int scnfg,append,endian;
static int level,seed;
static int nth,ntr,dtr_log,dtr_ms,dtr_cnfg;
static int ipgrd[2],flint;*/
static double *Wact,*Yact,*Qtop;

/*static char line[NAME_SIZE];
static char log_dir[NAME_SIZE],dat_dir[NAME_SIZE];
static char loc_dir[NAME_SIZE],cnfg_dir[NAME_SIZE];
static char log_file[NAME_SIZE],log_save[NAME_SIZE];
static char par_file[NAME_SIZE],par_save[NAME_SIZE];
static char dat_file[NAME_SIZE],dat_save[NAME_SIZE];
static char msdat_file[NAME_SIZE],msdat_save[NAME_SIZE];
static char rng_file[NAME_SIZE],rng_save[NAME_SIZE];
static char cnfg_file[NAME_SIZE],end_file[NAME_SIZE];
static char nbase[NAME_SIZE],cnfg[NAME_SIZE];*/
static FILE *fin=NULL,*flog=NULL,*fdat=NULL,*fend=NULL;

/*static lat_parms_t lat;
static bc_parms_t bcp;
static hmc_parms_t hmc;*/



static void alloc_data(void)
{
   int nn,tmax;
   int in;
   double **pp,*p;

   nn=file_head.nn;
   tmax=file_head.tmax;

   pp=malloc(3*(nn+1)*sizeof(*pp));
   p=malloc(3*(nn+1)*(tmax+1)*sizeof(*p));

   data.Wsl=pp;
   data.Ysl=pp+nn+1;
   data.Qsl=pp+2*(nn+1);

   for (in=0;in<(3*(nn+1));in++)
   {
      *pp=p;
      pp+=1;
      p+=tmax;
   }

   Wact=p;
   p+=nn+1;
   Yact=p;
   p+=nn+1;
   Qtop=p;
}

static void read_file_head(void)
{
   int iw;
   stdint_t istd[3];
   double dstd[1];

   iw=fread(istd,sizeof(stdint_t),3,fdat);
   iw+=fread(dstd,sizeof(double),1,fdat);

   /*(stdint_t)*/file_head.dn=istd[0];
   file_head.nn=istd[1];
   file_head.tmax=istd[2];
   file_head.eps=dstd[0];

}

static int read_data(void)
{
   int ir,nn,tmax;
   int in,t;
   stdint_t istd[1];
   double dstd[1];

   ir=fread(istd,sizeof(stdint_t),1,fdat);

   if (ir!=1)
      return 0;

   data.nt=(int)(istd[0]);

   nn=file_head.nn;
   tmax=file_head.tmax;

   for (in=0;in<=nn;in++)
   {
      for (t=0;t<tmax;t++)
      {
         ir+=fread(dstd,sizeof(double),1,fdat);

         data.Wsl[in][t]=dstd[0];
      }
   }

   for (in=0;in<=nn;in++)
   {
      for (t=0;t<tmax;t++)
      {
         ir+=fread(dstd,sizeof(double),1,fdat);

         data.Ysl[in][t]=dstd[0];
      }
   }

   for (in=0;in<=nn;in++)
   {
      for (t=0;t<tmax;t++)
      {
         ir+=fread(dstd,sizeof(double),1,fdat);

         data.Qsl[in][t]=dstd[0];
      }
   }

  
   return 1;
}


int main(void)
{
   fdat = fopen("../../test_run-09.05.2025/test_run/dat/run1_16b.ms.dat", "r");
   if (fdat == NULL) {
       perror("Errore apertura file");
       return 1;
   }

   read_file_head();  

   /*int tmax = file_head.tmax;
   int nn = file_head.nn;
   double eps = file_head.eps;
   int dn = file_head.dn;*/

   alloc_data();
   int nsweep = -1;
   while (read_data() == 1) 
   {
      nsweep++;
   }

   printf("%d" ,nsweep);


   int N = 1000;

   /* inizializza Qsl */
   double **Qsl = (double **)malloc(file_head.nn * sizeof(double *));
   for (int i = 0; i < file_head.nn; i++) 
   {
      Qsl[i] = (double *)calloc(nsweep , sizeof(double));
   }

   rewind(fdat);  
   read_file_head();  
   alloc_data();      

   for (int nsw = 0; nsw < nsweep; nsw++) 
   {
      read_data();
      for(int nw = 0; nw < file_head.nn; nw++)
      {
         for (int t = 0; t < file_head.tmax; t++) 
         {
            Qsl[nw][nsw] += data.Qsl[nw][t];
         }
      }

   }

   FILE *data;
   data=fopen("Q_16b.txt", "w");

   for (int i = 0; i<nsweep; i++)
   {
      for(int j = 0; j < file_head.nn; j++)
      {
         fprintf(data , "%f ", Qsl[j][i]);
      }
      fprintf(data , "\n ");
   }

/*-----------calcolo le Q quadro e le medio su ogni wilson time-----------*/

   /*inizializzo l'array media*/
   double *mean = (double *)malloc(file_head.nn * sizeof(double));
   for (int i = 0; i<file_head.nn; i++)
   {
      mean[i] = 0;
   }

   /*riempio l'array con la somma degli elementi*/
   for (int nw = 0 ; nw< file_head.nn; nw++)
   {
      for (int nsw = 0 ; nsw< nsweep; nsw++)
      {
         mean[nw] += Qsl[nw][nsw] * Qsl[nw][nsw];
      }
   }

   FILE *mean_file;
   mean_file=fopen("mean_16b.txt", "w");
   for (int i = 0; i < file_head.nn; i++)
   {
      fprintf(mean_file, "%f\n", mean[i]/nsweep);
   }


   for (int i = 0; i < 2; i++) 
   {
      free(Qsl[i]);
   }
   free(Qsl);
   fclose(fdat);

   return 0;
}