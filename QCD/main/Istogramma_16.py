import matplotlib
import numpy as np
import matplotlib.pyplot as plt

fig2, histo = plt.subplots(nrows=2, ncols=2, figsize=(10, 8))

dati_16 = np.loadtxt("Q_16.txt")
t0 = 49
histo[0][0].hist(dati_16[:,0], bins = 50, linewidth=2, color='red', alpha=0.8)
histo[0][0].set_title("t = 0", fontsize=14)
histo[0][0].set_xlabel("Carica Topologica $Q$", fontsize=11)
histo[0][0].set_ylabel("Frequenza", fontsize=11)

histo[0][1].hist(dati_16[:,int(0.1*t0)], bins = 50, linewidth=2, color='red', alpha=0.8)
histo[0][1].set_title("t = 0.1tO", fontsize=14)
histo[0][1].set_xlabel("Carica Topologica $Q$", fontsize=11)
histo[0][1].set_ylabel("Frequenza", fontsize=11)

histo[1][0].hist(dati_16[:,int(0.25*t0)], bins = 50, linewidth=2, color='red', alpha=0.8)
histo[1][0].set_title("t = 0.25t0", fontsize=14)
histo[1][0].set_xlabel("Carica Topologica $Q$", fontsize=11)
histo[1][0].set_ylabel("Frequenza", fontsize=11)

histo[1][1].hist(dati_16[:,int(t0)], bins = 50, linewidth=2, color='red', alpha=0.8)
histo[1][1].set_title("t = t0", fontsize=14)
histo[1][1].set_xlabel("Carica Topologica $Q$", fontsize=11)
histo[1][1].set_ylabel("Frequenza", fontsize=11)

plt.tight_layout()
plt.savefig('Risultati/Istogramma_16.png', dpi=300)