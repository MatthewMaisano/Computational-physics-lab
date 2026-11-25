import matplotlib
from scipy.optimize import curve_fit
import numpy as np
import matplotlib.pyplot as plt
import sys
sys.path.append('/mnt/c/Users/havef/OneDrive/Desktop/LFC/QCD/librerie')
import Jacknife as j
import fit_pack as FIT

Q_err = np.zeros((4))
Q = np.zeros((4))

with open('varianze.txt', 'r') as file:
    righe = file.readlines()
    
    for riga in righe:
        var = float(riga.strip()) # .strip() rimuove \n, float() converte
        var.append(numero)
print(var)
#FIT.fit_function(var, x, y)
plt.savefig('/mnt/c/Users/havef/OneDrive/Desktop/LFC/QCD/Risultati/Fit_primo_valore.png', dpi=300)

#--------------------------------------------------------------------------------#