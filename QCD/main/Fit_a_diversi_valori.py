import matplotlib
from scipy.optimize import curve_fit
import numpy as np
import matplotlib.pyplot as plt
import sys
sys.path.append('../librerie')
import Jacknife as j
from fit_pack import fit_function
#-----------------------------------------------------------------------------#

dati_20 = np.loadtxt("Q_20.txt")
medie_20 = np.loadtxt("mean_20.txt")

dati_16 = np.loadtxt("Q_16.txt")
medie_16 = np.loadtxt("mean_16.txt")

dati_16b = np.loadtxt("Q_16b.txt")
medie_16b = np.loadtxt("mean_16b.txt")

dati_12 = np.loadtxt("Q_12.txt")
medie_12 = np.loadtxt("mean_12.txt")

#------------------------------------------------------------------------------#
#Funzione per fittare a t0 fissato#
def fit_Singolo_valore(multiple):
    t0 = np.array([28 , 49 , 38 , 62])

    t01= np.zeros((4))
    for i in range(np.size(t0)):
        t01[i] = t0[i]/multiple

    media_12_0 = medie_12[int(t01[0])]
    media_16_0 = medie_16[int(t01[1])]
    media_16b_0 = medie_16b[int(t01[2])]
    media_20_0 = medie_20[int(t01[3])]

    t0_over_a2 = np.zeros((4))

    values = [2.79 , 4.87 , 3.78, 6.20]
    for i in range(np.size(values)):
        t0_over_a2[i] = float(values[i])
    
    num=np.array([])    
    for i in values:
        num = np.append(num, i)
    
    x1 = 1/num
    means = [media_12_0/12**4, media_16_0/16**4, media_16b_0/16**4, media_20_0/20**4]
    y1 = means *(num)**2

    var20 = j.jack(dati_20, t01[3], 20, multiple)
    var16 = j.jack(dati_16, t01[1], 16,multiple) #
    var16b = j.jack(dati_16b, t01[2], 16,multiple)
    var12 = j.jack(dati_12, t01[0], 12,multiple)
    var1 = [var12,var16,var16b,var20]

    popt , perr = fit_function(x1,y1,var1,multiple)
    return popt, perr


#-------------------------------------------------------------------------------#

Q = np.zeros((4))
Q_err = np.zeros((4))
scale_factor = np.array([1,2,4,4/3])

for i in range(np.size(scale_factor)):
    popt, perr = fit_Singolo_valore(scale_factor[i])
    
    
    Q[i] = popt[1]
    Q_err[i] = perr[1]


#--------------------------------------------------------------------------------#
#Limite al continuo#
plt.errorbar(1/scale_factor, Q, Q_err, fmt='.k', ecolor='gray', lw=1, label='Dati')

def model_f(x,a):
    return np.full_like(x, a) 


popt, pcov = curve_fit(model_f, 1/scale_factor, Q, sigma = Q_err, p0=[1])
a_opt = popt
xl_model = np.linspace(0, max(1/scale_factor), 100)
yl_model = model_f(xl_model, a_opt)

dof = len(1/scale_factor)-len(popt)
chi2_red = np.sum((Q - model_f(np.array(1/scale_factor),a_opt))**2 / (np.array(Q_err))**2)/dof

plt.plot(xl_model,yl_model, color='r')
perr = np.sqrt(np.diag(pcov))
Nf = 3
f = 109.6 
t0 = (0.176)**2/(197.327)**2
chi = (popt/t0**2)**0.25
chi_err = (perr/t0**2)**0.25
print('valore medio trovato: ',popt, perr)
print('suscettività:', chi, chi_err)
plt.title(f'Fit del valor medio, chi: {chi2_red}')
plt.savefig('/mnt/c/Users/havef/OneDrive/Desktop/LFC/QCD/Risultati/Fit_valor_medio.png')

