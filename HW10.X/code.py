# Write your code here :-)
from ulab import numpy as np # to get access to ulab numpy functions
import math
import time
#from ulab.scipy import signal

x = np.linspace(0,2*math.pi,1024)
sinwave1 = np.zeros(1024)
sinwave2 = np.zeros(1024)
sinwave3 = np.zeros(1024)
combinedsin = np.zeros(1024)

# Declare sin wave arrays
amp = 1
for j in range(1024):
    sinwave1[j] = amp * np.sin(10*x[j])
    sinwave2[j] = amp * np.sin(20*x[j])
    sinwave3[j] = amp * np.sin(30*x[j])
    combinedsin[j] = sinwave1[j]+sinwave2[j]+sinwave3[j]

real, imag = np.fft.fft(combinedsin)
flag = 0
i = 0

while flag != 1:
    #print((sinwave1[i],sinwave2[i],sinwave3[i],combinedsin[i]))
    print((real[i],))
    print(i)
    time.sleep(0.005)
    i = i+1
    if i == 1024:
        flag = 1
