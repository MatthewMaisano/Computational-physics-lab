import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import lognorm  # <--- CAMBIAMENTO 1

x1 = []

# (Il tuo metodo di lettura file va bene, ma np.loadtxt è più veloce se hai solo numeri)
try:
    f = open("Distrib_x1.txt", "r")
    for line in f.readlines():
        x1 = np.append(x1, float(line))
    f.close()
except FileNotFoundError:
    # Genero dati finti solo per farti vedere che il codice funziona se non hai il file
    print("File non trovato, uso dati generati casualmente.")
    x1 = np.random.lognormal(mean=2.0, sigma=0.5, size=1000)

# --- FITTING ---
# lognorm.fit restituisce 3 valori:
# s (shape) = sigma (deviazione standard del logaritmo)
# loc = spostamento (se i tuoi dati partono da 0, questo dovrebbe essere vicino a 0)
# scale = exp(mu) (dove mu è la media del logaritmo)
shape, loc, scale = lognorm.fit(x1) # <--- CAMBIAMENTO 2

# Calcoliamo mu e sigma "fisici" dai parametri del fit
mu_log = np.log(scale) 
sigma_log = shape

print(f"Parametri trovati:")
print(f"Sigma (shape): {sigma_log:.4f}")
print(f"Mu (dal logaritmo): {mu_log:.4f}")
print(f"Scale (exp(mu)): {scale:.4f}")
print(f"Loc (spostamento): {loc:.4f}")

# --- PLOTTING ---
plt.figure(figsize=(10, 6))

# Istogramma
plt.hist(x1, bins=100, density=True, alpha=0.6, color='skyblue', edgecolor='black', label='Dati osservati')

# Curva Fittata
xmin, xmax = plt.xlim()
x = np.linspace(xmin, xmax, 200) # Uso 200 punti per renderla più morbida

# lognorm.pdf richiede (x, s, loc, scale)
p = lognorm.pdf(x, shape, loc, scale) # <--- CAMBIAMENTO 3

plt.plot(x, p, 'r', linewidth=2, label=f'Fit Log-Norm ($\sigma$={sigma_log:.2f}, $\mu$={mu_log:.2f})')

# Dettagli estetici
plt.title('Istogramma con Fit Log-Normale')
plt.xlabel('Valori')
plt.ylabel('Densità di Probabilità')
plt.legend()
plt.grid(True, alpha=0.3)
plt.show()


