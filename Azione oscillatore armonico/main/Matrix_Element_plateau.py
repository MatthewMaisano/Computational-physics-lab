import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
Matrix = [] 
t = []
Sigma = []

f = open("Matrix.txt", "r")
for line in f.readlines():
	Matrix.append(float(line))
f.close()

k = open("tempo_fisico.txt", "r")
for line in k.readlines():
	t.append(float(line))

c = open("Jack_Matr.txt","r")
for line in c.readlines():
	Sigma.append(np.sqrt(float(line)))

def model_f(x,m,q):
    return m*x + q

l = 5
t_reduct = t[:l]
Matrix_reduct = Matrix[:l]
Sigma_reduct = Sigma[:l]

weight = np.zeros(l)
for i in range(l):
	weight[i] = 1/(Sigma_reduct[i])**2

Sigma_Matrix = np.sqrt(1/sum(weight))


Matr_0 = 0
for i in range (l):
	Matr_0 += Matrix_reduct[i] * weight[i] / sum(weight)

plt.title("Plateau dell'elemento di matrice", fontsize=14, fontweight='bold')
plt.xlabel("tempo fisico", fontsize=12)
plt.ylabel("Elemento di matrice", fontsize=12)
plt.errorbar(t_reduct,Matrix_reduct,Sigma_reduct,fmt='ro', ecolor='black', capsize=3)
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('plateau_elemento_di_matrice')
print(Matr_0,Sigma_Matrix)

