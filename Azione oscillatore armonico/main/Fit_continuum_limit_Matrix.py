import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
M0= [] 
M0_sigma = []

f = open("Matrix_continuum.txt", "r")
for line in f.readlines():
	M0.append(float(line))
f.close()

k = open("Matrix_continuum_sigma.txt", "r")
for line in k.readlines():
	M0_sigma.append(float(line))
k.close()

passo = [1, 1/2, 1/2.5, 1/4, 1/8, 1/16]


def model_f(x,a,b,d):
    return a + b*(x**2) + d*(x**4) 


popt, pcov = curve_fit(model_f, passo, M0, sigma = M0_sigma, p0=[1,1,1])
a_opt, b_opt, d_opt = popt
x_model = np.linspace(min(passo), max(passo), 100)
y_model = model_f(x_model, a_opt, b_opt, d_opt)

dof = len(passo)-len(popt)
chi2_red = np.sum((M0 - model_f(np.array(passo),a_opt,b_opt,d_opt))**2 / (np.array(M0_sigma))**2)/dof

plt.title("Fit del limite al continuo dell'elemento di matrice", fontsize=14, fontweight='bold')
plt.xlabel("passo reticolare (a)", fontsize=12)
plt.ylabel("Elemento di matrice ", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.errorbar(passo,M0,M0_sigma,fmt='ro', ecolor='black', capsize=3)
plt.plot(x_model,y_model, color='k')
plt.savefig('Limite_al_continuo_el_matrice')
perr = np.sqrt(np.diag(pcov))
print(popt,perr,chi2_red)

