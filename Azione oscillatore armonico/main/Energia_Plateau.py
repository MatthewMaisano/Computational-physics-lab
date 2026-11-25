import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
Energy = [] 
t = []
Sigma = []

f = open("Energy.txt", "r")
for line in f.readlines():
	Energy.append(float(line))
f.close()

k = open("tempo_fisico.txt", "r")
for line in k.readlines():
	t.append(float(line))

c = open("Jack_E.txt","r")
for line in c.readlines():
	Sigma.append(np.sqrt(float(line)))

def model_f(x,m,q):
    return m*x + q

l = 5
t_reduct = t[:l]
Energy_reduct = Energy[:l]
Sigma_reduct = Sigma[:l]

weight = np.zeros(l)
for i in range(l):
	weight[i] = 1/(Sigma_reduct[i])**2

Sigma_E0 = np.sqrt(1/sum(weight))


E0 = 0
for i in range (l):
	E0 += Energy_reduct[i] * weight[i] / sum(weight)

plt.xlabel("Delta Energia ($E(t)$)", fontsize=12)
plt.ylabel("Tempo fisico ($t$)", fontsize=12)
plt.title("Plateau dell'energia", fontsize=14)
plt.errorbar(t_reduct,Energy_reduct,Sigma_reduct,fmt='ro', ecolor='black', capsize=3)
plt.savefig('E_plateau.png', dpi=300)
#plt.show()
print(E0,Sigma_E0)

