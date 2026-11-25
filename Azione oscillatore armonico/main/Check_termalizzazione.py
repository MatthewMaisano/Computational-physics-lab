import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
action = [] 


f = open("Action_check_therm.txt", "r")
for line in f.readlines():
	action.append(float(line))
f.close()
tM = np.linspace(0,np.size(action),np.size(action))

l = 100
tM_plot = tM[:l]
action_plot = action[:l]
n_cut = 10

plt.xlabel('tempo_Markoviano')
plt.ylabel('Valore azione')
plt.title('Monitoraggio della Termalizzazione')
plt.axvline(x=n_cut, color='red', linestyle='--', linewidth=2, label=f'Taglio termalizzazione ({n_cut})')
plt.plot(tM_plot,action_plot, color = 'green')
plt.savefig('Therm_graphic')


