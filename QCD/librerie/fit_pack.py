import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def fit_function(var, x, y):
    def model(x, a, b):
        return a*x + b

    # Eseguo il fit
    popt, pcov = curve_fit(model, x, y, p0=[0.4, 0.0005], sigma=var)
    perr = np.sqrt(np.diag(pcov))

    # Genero i punti per la linea del fit
    x_model = np.linspace(0, max(x), 1000)
    y_model = model(x_model, *popt)

    # Plot
    plt.errorbar(x, y, var, fmt='.k', ecolor='gray', lw=1, label='Dati')
    plt.errorbar(0, popt[1], perr[1], fmt='.r', ecolor='red', lw=1, label='Limite Continuo')
    plt.plot(x_model, y_model, color='red', label='Fit lineare')
    plt.title('Fit valori ottimali')
    plt.grid()
    plt.legend()
    # plt.show() # Meglio non metterlo qui per poter aggiungere label dopo
    
    return popt, perr

#--------------------------------------------------------------------------------#