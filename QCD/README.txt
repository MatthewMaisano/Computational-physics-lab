In questa sezione non è presente un makefile siccome i passaggi sono molto più semplici e richiedono una quantità minore di codice

-Nella cartella "Main" sono presenti:


-"Fit_a_diversi_valori.py", il quale calcola il fit per la suscettività topologica a diversi valori del Wilson time (4 valori) e genera 4 fit
A schermo possono essere visualizzati il valor medio dell'intercetta del fit con il suo errore associato con la rispettiva varianza e il valore della suscettività topologica calcolato dividendo tale valore per t0^2 e prendendo la radice quarta.


-"Istogrammi_i.py" (con i che rappresenta l'indice degli istogrammi che si vuole generare) i quali creano i grafici della distribuzione della suscettività topologica per 4 valori di Wilson time.

nella libreria sono presenti altri due file, il primo "Jacknife.py" calcola la varianza del valor medio della suscettività al quadrato attraverso il metodo Jackknife, mentre "fit_pack" viene utilizzato in "Fit_a_diversi_valori" per creare i fit della suscettività.