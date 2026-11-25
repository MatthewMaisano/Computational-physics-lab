
#ifndef JACKNIFE_H
#define JACKNIFE_H

#ifndef JACKNIFE_C
extern double sigmaJack(double **Jack_Bin, int j);
extern double *jack_end();
extern void fill_xxBin(int j,double diff);
extern void fill_JackBin(int bin_index, int j, double diff);
extern int fill_bin(int bin_index, int i,int Dim_bin);

#endif
#endif