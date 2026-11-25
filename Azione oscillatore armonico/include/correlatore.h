#ifndef CORRELATORE_H
#define CORRELATORE_H

#ifndef CORRELATORE_C
extern double correlator(int t);
extern double autocorrelator(int t, int k);
extern void fill_correlator();
extern void emptyBin();
extern double BinCorrelator(int t);
extern double sigmaJack(double **Jack_Bin, int j);
extern void fill_corr_tmarkov(int i);
extern double *compute_sigma();
#endif
#endif