#ifndef ACTION_H
#define ACTION_H

#ifndef ACTION_C
extern double action();
extern double actionprov(double x[]);
extern double Deltax(int i);
extern double DeltaS(int i);
extern double Mini_action(int j);
extern double NewDeltaS(double k, int j);
extern double compute_DeltaS(int i, double x_old, double x_new);


#endif
#endif