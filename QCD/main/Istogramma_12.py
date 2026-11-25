import matplotlib
import numpy as np
import matplotlib.pyplot as plt

fig2, histo = plt.subplots(nrows=2, ncols=2, figsize=(10, 8))

dati_12 = np.loadtxt("Q_12.txt")
t0 = 28
histo[0][0].hist(dati_12[:,0], bins = 50, linewidth=2, color='skyblue', alpha=0.8)

histo[0][1].hist(dati_12[:,int(0.1*t0)], bins = 50, linewidth=2, color='skyblue', alpha=0.8)

histo[1][0].hist(dati_12[:,int(0.25*t0)], bins = 50, linewidth=2, color='skyblue', alpha=0.8)

histo[1][1].hist(dati_12[:,int(t0)], bins = 50, linewidth=2, color='skyblue', alpha=0.8)

plt.savefig('Risultati/Istogramma_12.png', dpi=300)

