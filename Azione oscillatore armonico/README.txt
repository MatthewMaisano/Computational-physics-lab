Ecco delineati i singoli passaggi per eseguire i programmi nell'ordine corretto :

Digitare i comandi a terminale nel seguente ordine:
--COMPILAZIONE--
1)  make

--GENERAZIONE DATI--
2) ./Main_generazione
3) python3 autocorr.py
4)	./Main_Binnaggio

--ANALISI DATI--
-- Ora i dati sono stati generati correttamente e anche binnati per eliminare l'autocorrelazione tra cammini su sweep diversi.
5)	./Main_Analisi


--	Ora i dati sono stati utilizzati nell'analisi e sono state calcolare le quantità a cui si è interessati.
è possibile eseguire i seguenti programmi nell'ordine preferito:
- python3 Energia_plateau.py
- python3 Matrix_Element_plateau.py
il numero di punti usato per il fit è deciso al momento controllando il grafico e i due programmi restituiscono a schermo i valori dell'energia e dell'elemento di matrice trovati eseguendo la media pesata tra i primi n.


--LIMITE AL CONTINUO---
--Per eseguire il limite al continuo basta eseguire i seguenti programmi:

- python3 Fit_continuum_limit.py
- python3 Fit_continuum_limit_Matrix.py

è possibile anche eseguire questi ultimi due programmi prima degli altri in quanto i dati che cui fanno riferimento sono scritti a mano controllando i valori restituiti a schermo dai due precedenti.

--CHECK--
 sono presenti due check: 
 il primo "Check_termalizzazione.py" controlla che la termalizzazione sia avvenuta con successo, plottando i valori dell'azione in funzionedel numero di sweep
 il secondo "Check_Annullarsi_Autocorr.c" confronta i valori dell'errore del correlatore binnato ottenuto senza tenere conto dell'autocorrelazione e lo stesso errore ma col jackknife (il quale ne tiene conto), se sono uguali significa che il binnnaggio è avvenuto con successo e l'autocorrelazione è andata a zero

