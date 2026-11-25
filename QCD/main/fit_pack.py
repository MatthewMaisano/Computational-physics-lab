import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def fit_function(x, y, var,multiple):
    def model(x, a, b):
        return a*x + b

    # Eseguo il fit
    popt, pcov = curve_fit(model, x, y, p0=[0.4, 0.0005], sigma=var)
    perr = np.sqrt(np.diag(pcov))
    a_opt ,b_opt = popt

    # Genero i punti per la linea del fit
    x_model = np.linspace(0, max(x), 1000)
    y_model = model(x_model, *popt)

    #chi quadro ridotto
    dof = len(x)-len(popt)
    chi2_red = np.sum((y - model(np.array(x),a_opt,b_opt))**2 / (np.array(var))**2)/dof

    # Plot
    plt.errorbar(x, y, var, fmt='.k', ecolor='gray', lw=1)
    plt.errorbar(0, popt[1], perr[1], fmt='.r', ecolor='red', lw=1, label='Limite Continuo')
    plt.plot(x_model, y_model, color='red')
    plt.title(f'Fit a {1/multiple} t0')
    plt.grid()
    plt.legend()
    plt.savefig(f'Risultati/Fit_a_{multiple}.png') 
    plt.close()
    print(popt[1],perr[1] , 1/multiple)
    return popt, perr

#--------------------------------------------------------------------------------#