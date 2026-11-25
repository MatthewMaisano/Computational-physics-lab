
/*******************************************************************************
*
* File global.h
*
* Global parameters and arrays
*
*******************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#define N 64
#define a 1.
#define m 1.
#define w 1.
#define DELTA 1.
#define therm 500
#define K 20
#define SweepInit 100000
#define tphys 2
#define Nbin 10000

#if defined MAIN_PROGRAM
  #define EXTERN
#else
  #define EXTERN extern
#endif

/*forse conviene definire dinamicamente le cose che dopo non scrivo su file e le altre non dinamicamente*/
EXTERN double xx[N];
EXTERN double r[N];
EXTERN double rComp[N];
EXTERN double CorrtMarkov[SweepInit][N-1];
EXTERN double xxBin[N];
EXTERN double E[N-2];
EXTERN double Matr[N-2];
EXTERN double *sum;
EXTERN double **Matr_Jack;
EXTERN double **E_Jack;
EXTERN double **Jack_Bin;
EXTERN double *xxBinQuad;
EXTERN double *corr;
EXTERN double *D;
EXTERN double *corrQuad;


#undef EXTERN

#endif

