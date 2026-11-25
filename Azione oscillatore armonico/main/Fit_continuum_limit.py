import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
E0= [] 
E0_sigma = []

f = open("E0.txt", "r")
for line in f.readlines():
	E0.append(float(line))
f.close()

k = open("E0_sigma.txt", "r")
for line in k.readlines():
	E0_sigma.append(float(line))
k.close()

passo = [1, 1/2, 1/2.5, 1/4, 1/8, 1/16]


def model_f(x,a,b,c):
    return a + b*(x**2) + c*(x**4)


popt, pcov = curve_fit(model_f, passo, E0, sigma = E0_sigma, p0=[1,1,1])
a_opt, b_opt, c_opt = popt
x_model = np.linspace(min(passo), max(passo), 100)
y_model = model_f(x_model, a_opt, b_opt, c_opt)

dof = len(passo)-len(popt)
chi2_red = np.sum((E0 - model_f(np.array(passo),a_opt,b_opt,c_opt))**2 / (np.array(E0_sigma))**2)/dof

plt.title("Fit del limite al continuo dell'energia", fontsize=14, fontweight='bold')
plt.xlabel("passo reticolare (a)", fontsize=12)
plt.ylabel("Energia ", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.errorbar(passo,E0,E0_sigma,fmt='ro', ecolor='black', capsize=3)
plt.plot(x_model,y_model, color='k')
plt.savefig('Limite_al_continuo_Energia')
perr = np.sqrt(np.diag(pcov))
print(popt,perr,chi2_red)

