#define PRINT

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "global.h"
#include "trajectory.h"
#include "utility.h"
#include "correlatore.h"
#include "var_init.h"
#include <string.h>

#define PI 3.141592653589793 

/*stampo i valori dell'autocorrelazione per eseguire il fit*/
void Print_autocorr()
{
	FILE *data;
   	data=fopen("Dati.txt", "w");

   	FILE *tMarkov;
   tMarkov=fopen("tMarkov.txt", "w");

   	double autocorr;
   	double autocorr_0;
	for (int tmarkov=0; tmarkov<SweepInit-1; tmarkov++)
   	{
   		autocorr = autocorrelator(tmarkov,tphys);
   		autocorr_0 = autocorrelator(0,tphys);
      	fprintf(data, "%lf \n", autocorr/autocorr_0);

      	fprintf(tMarkov, "%d \n", tmarkov);
   	}
   	fprintf(data , "%d\n", N);
}

void Print_jack_bin()
{

	FILE *Jacknife;
   	Jacknife=fopen("Cluster_Jack.txt", "w");
   	for (int i = 0; i < Nbin; i++)
   	{
      	for(int j = 0; j < N-1; j++)
      	{
         	fprintf(Jacknife, "%lf  ", Jack_Bin[i][j]);
      	}
      	fprintf(Jacknife, "\n");
   	}
}

void Print_sigma_jack()
{

	double sigma_E[N-3];

	FILE *Sigma_jack_E;
   	Sigma_jack_E=fopen("Jack_E.txt", "w");
   	for (int t_phys = 0; t_phys < N-2; t_phys++)
   	{
      	sigma_E[t_phys] = sigmaJack(E_Jack, t_phys);
      	fprintf(Sigma_jack_E, "%lf \n", sigma_E[t_phys]);
   	}
}

void Print_jack_matr()
{
	
	double sigma_M[N-2];

   	FILE *Sigma_jack_Matr;
   	Sigma_jack_Matr=fopen("Jack_Matr.txt", "w");
   	for (int t_phys = 0; t_phys < N-2; t_phys++)
	{
	    sigma_M[t_phys] = sigmaJack(Matr_Jack, t_phys);
      	fprintf(Sigma_jack_Matr, "%9e \n", sigma_M[t_phys]);
   	}
}

void Print_check(double *sigma_jack)
{
	FILE *Check;
   	Check = fopen("Check_Annullarsi_autocorr.txt", "w");

	double sigmaBin[N-1];
   	for(int t=0; t<N-1; t++)
   	{
      	sigmaBin[t] = (xxBinQuad[t]/Nbin - pow((xxBin[t]/Nbin),2))/(Nbin-1);
      	fprintf(Check , "Var Bin = %9e  jack: %9e \n", sigmaBin[t], sigma_jack[t]);
   	}	
}

void Print_all()
{
	Print_autocorr();
	Print_jack_bin();
	Print_sigma_jack();
	Print_jack_matr();
	/*Print_corr();
	Print_corrBin();*/
}

void Read_jack_cluster()
{

    FILE *Cluster;
    Cluster = fopen("Cluster_Jacknife.txt", "r");

    /*Leggo dei dati tramite cicli annidati*/
    for (int i = 0; i < Nbin; i++) 
    {
        for (int j = 0; j < N-1; j++) 
        {
            if (fscanf(Cluster, "%lf", &Jack_Bin[i][j]) != 1) 
   			{
    			fprintf(stderr, "Errore\n");
    			fclose(Cluster);
   				exit(1);
   			}
        }
    }

    /*Chiudo il file*/
    fclose(Cluster);
}
void Print_Corr_Mediati()
{

	FILE *Corr_Mediati;
   	Corr_Mediati=fopen("Corr_Mediati.txt", "w");

   	for (int j = 0;j<N;j++)
   	{
      	fprintf(Corr_Mediati, "%lf ", xxBin[j]);
   	}
   	fprintf(Corr_Mediati,"\n");

   	for (int j = 0;j<N;j++)
   	{
      	fprintf(Corr_Mediati, "%lf ", xxBinQuad[j]);
   	}
}
void Print_Jack_Cluster()
{

	FILE *Cluster_jack;
   	Cluster_jack=fopen("Cluster_Jacknife.txt", "w");
   
   	for (int i=0; i < Nbin; i++)
   	{
      	for (int j = 0;j<N-1;j++)
      	{
         	fprintf(Cluster_jack, "%lf ", Jack_Bin[i][j]);
      	}
      	fprintf(Cluster_jack, "\n");
   	}
}
void Read_Corr_Mediati()
{

    FILE *Corr_Med;
    Corr_Med = fopen("Corr_Mediati.txt", "r");

    /*Leggo dei dati tramite cicli annidati*/
  	for (int j = 0; j < N; j++) 
   	{
     	if(fscanf(Corr_Med, "%lf", &xxBin[j])!=1)
     	{
    		fprintf(stderr, "Errore\n");
    		fclose(Corr_Med);
   			exit(1);
     	}
  	}
  	for (int j = 0; j < N; j++) 
   	{
     	if(fscanf(Corr_Med, "%lf", &xxBinQuad[j])!=1)
     	{
    		fprintf(stderr, "Errore\n");
    		fclose(Corr_Med);
   			exit(1);     		
     	}
  	}

    /*Chiudo il file*/
    fclose(Corr_Med);
}