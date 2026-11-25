import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
Autocorr = np.array([]) 
t = []

f = open("Dati.txt", "r")
for line in f.readlines():
	Autocorr = np.append(Autocorr,float(line))
f.close()

k = open("tMarkov.txt", "r")
for line in k.readlines():
	t.append(float(line))

ln_autocorr = np.log(Autocorr + abs(min(Autocorr))+1)


l = int(10 * np.sqrt(Autocorr[-1]/64))
t_reduct = t[:l]
Autocorr_reduct = np.log(Autocorr[:l])


def model_f(x,m,q):
    return m*x + q
popt, pcov = curve_fit(model_f, t_reduct, Autocorr_reduct, p0=[-0.08,-5])
m_opt, q_opt = popt
x_model = np.linspace(min(t_reduct), max(t_reduct), 100)
y_model = model_f(x_model, m_opt, q_opt)

plt.xlabel("Tempo Markoviano ($t$)", fontsize=12)
plt.ylabel("Autocorrelazione $C(t_M)$", fontsize=12)
plt.title("Analisi dell'Autocorrelazione", fontsize=14)

plt.scatter(t_reduct,Autocorr_reduct, s=5, color='k')
plt.plot(x_model,y_model, color='r')
plt.savefig(f'Tempo_autocorr_')
print(-1/m_opt)

with open('Autocorrelation_time.txt', 'w', encoding='utf-8') as f:
    f.write(str(int(-1/m_opt+1)*10))

