import matplotlib
import numpy as np
import matplotlib.pyplot as plt
import sys
sys.path.append('/mnt/c/Users/havef/OneDrive/Desktop/LFC/QCD/librerie')
import Jacknife as j

dati_20 = np.loadtxt("/mnt/c/Users/havef/OneDrive/Desktop/openQCD/openQCD-1.4/main/Q_20.txt")
medie_20 = np.loadtxt("/mnt/c/Users/havef/OneDrive/Desktop/openQCD/openQCD-1.4/main/mean_20.txt")

dati_16 = np.loadtxt("/mnt/c/Users/havef/OneDrive/Desktop/openQCD/openQCD-1.4/main/Q_16.txt")
medie_16 = np.loadtxt("/mnt/c/Users/havef/OneDrive/Desktop/openQCD/openQCD-1.4/main/mean_16.txt")

dati_16b = np.loadtxt("/mnt/c/Users/havef/OneDrive/Desktop/openQCD/openQCD-1.4/main/Q_16b.txt")
medie_16b = np.loadtxt("/mnt/c/Users/havef/OneDrive/Desktop/openQCD/openQCD-1.4/main/mean_16b.txt")

dati_12 = np.loadtxt("/mnt/c/Users/havef/OneDrive/Desktop/openQCD/openQCD-1.4/main/Q_12.txt")
medie_12 = np.loadtxt("/mnt/c/Users/havef/OneDrive/Desktop/openQCD/openQCD-1.4/main/mean_12.txt")

varianze = "/mnt/c/Users/havef/OneDrive/Desktop/LFC/QCD/Risultati/varianze.txt"
x_file = "/mnt/c/Users/havef/OneDrive/Desktop/LFC/QCD/Risultati/varianze.txt"
y_file = "/mnt/c/Users/havef/OneDrive/Desktop/LFC/QCD/Risultati/varianze.txt"

t0 = np.array([28 , 49 , 38 , 62])
t01 = t0
media_12_0 = medie_12[t0[0]]
media_16_0 = medie_16[t0[1]]
media_16b_0 = medie_16b[t0[2]]
media_20_0 = medie_20[t0[3]]
#plt.scatter(index, medie, s=4)
#index = np.arange(0,np.size(medie))
t0_over_a2 = np.zeros((4))

values = [279 , 487 , 378, 620] #le uso dividendo per 100
for i in range(np.size(values)):
    t0_over_a2[i] = float(values[i])
    
num=np.array([])    
for i in values:
    num = np.append(num, i)
    
x = 1/num
means = [media_12_0/12**4, media_16_0/16**4, media_16b_0/16**4, media_20_0/20**4]
y = means *(num/100)**2

#calcolo varianza con jacknife
var20 = j.jack(dati_20,62,20)
var16 = j.jack(dati_16,49,16) 
var16b = j.jack(dati_16b,38,16)
var12 = j.jack(dati_12,28,12)
var = [var12,var16b,var16,var20]
print(var12,var16b,var16,var20)

with open(varianze , 'w') as v:
    for i in var:
        v.write(str(i) + '\n')

with open(x_file , 'w') as x_f:
    for k in x:
        x_f.write(str(k) + '\n')

with open(y_file , 'w') as y_f:
    for j in y:
        y_f.write(str(j) + '\n')

plt.errorbar(x, y, var ,fmt='ro', ecolor='black', capsize=3)
#plt.show()
plt.savefig('/mnt/c/Users/havef/OneDrive/Desktop/LFC/QCD/Risultati/Medie.png', dpi=300)