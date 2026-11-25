import matplotlib
import numpy as np
import matplotlib.pyplot as plt

fig2, histo = plt.subplots(nrows=2, ncols=2, figsize=(10, 8))

dati_16b = np.loadtxt("Q_16b.txt")
t0 = 38
histo[0][0].hist(dati_16b[:,0], bins = 50, linewidth=2, color='skyblue', alpha=0.8)

histo[0][1].hist(dati_16b[:,int(0.1*t0)], bins = 50, linewidth=2, color='skyblue', alpha=0.8)

histo[1][0].hist(dati_16b[:,int(0.25*t0)], bins = 50, linewidth=2, color='skyblue', alpha=0.8)

histo[1][1].hist(dati_16b[:,int(t0)], bins = 50, linewidth=2, color='skyblue', alpha=0.8)
plt.savefig('Risultati/Istogramma_16b.png', dpi=300)