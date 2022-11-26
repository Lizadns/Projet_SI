import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

data_Philosophe= pd.read_csv('mesuresPhilosophe.csv', sep = ',')
data_time=data_Philosophe['time']
data_thread=data_Philosophe['thread']

data_2=data_time[data_thread==2]
data_3=data_time[data_thread==3]
data_4=data_time[data_thread==4]

mean_2=data_2.mean()
mean_3=data_3.mean()
mean_4=data_4.mean()

fig1 = plt.figure()
T=[mean_2,mean_3,mean_4]

M = [i for i in range(6,8)]
plt.plot(M, T, color="blue", linewidth=1.0, linestyle="-")

plt.xlim(1,4)
plt.xticks(np.linspace(1,4,4))

plt.ylim(0,60)
plt.yticks(np.linspace(0,60,13))

plt.show()
plt.close()

