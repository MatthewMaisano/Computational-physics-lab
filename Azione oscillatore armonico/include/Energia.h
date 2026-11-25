#ifndef ENERGIA_H
#define ENERGIA_H

#ifndef ENERGIA_C
extern void Energy();
extern void Energy_Jack(double **jack, double **E);
extern void printEnergy();
extern void print_t();
extern void Elemento_matr();
extern void Elemento_matr_Jack(double **jack, double **E, double **Matr);
extern void printMatr();
#endif
#endif