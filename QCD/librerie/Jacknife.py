import matplotlib
import numpy as np
import matplotlib.pyplot as plt

def jack(data, line, a, multiple):
	t0 = np.array([28 , 49 , 38 , 62])

	t0_over_a2 = np.zeros((4))
	values = [2.79 , 4.87 , 3.78, 6.20] #le uso dividendo per 100
	for i in range(np.size(values)):
		t0_over_a2[i] = float(values[i])

	new_data = data[:,int(line)]**2
	jack_var = np.array([])
	N = np.size(new_data)
	jack_err = 0
    
	index = np.where(t0 == line * multiple)[0][0]
    
	for i in range(N):
		#trovo variabili clusterizzate, divido per a^4 e moltiplico per (t0/a^2)**2
		jack_var = np.append(jack_var, (1/(N-1)) * (np.sum(new_data) - new_data[i])/(a**4) * ((t0_over_a2[index])**2))
        
	for i in range (N):
		jack_err += (N-1)/N * (jack_var[i] - np.mean(jack_var))**2
	
	return np.sqrt(jack_err)