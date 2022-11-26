import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


data_Philosophe= pd.read_csv('../Projet_SI/Projet_SI/mesuresPhilosophe.csv', sep = ',')
data_time=data_Philosophe['time']
data_thread=data_Philosophe['thread']

data_1=data_time[data_thread==1]
data_2=data_time[data_thread==2]
data_3=data_time[data_thread==3]
data_4=data_time[data_thread==4]

"""""
mean_1=data_1.mean()
mean_2=data_2.mean()
mean_3=data_3.mean()
mean_4=data_4.mean()

fig1 = plt.figure()
T=[mean_2,mean_3,mean_4]

M = [i for i in range(2,5)]
plt.plot(M, T, color="blue", linewidth=1.0, linestyle="-")

plt.xlim(1,4)
plt.xticks(np.linspace(1,4,4))

plt.ylim(0,30)
plt.yticks(np.linspace(0,30,14))

plt.show()
plt.close()
"""""


#boite à moustache Philosophe
fig2=plt.figure()
plt.boxplot([data_2,data_3,data_4], labels=[2,3,4])
plt.ylabel('Time')
plt.title('Box plot Philosophe')
plt.show()
plt.close()

data_Pro=pd.read_csv('../Projet_SI/Projet_SI/mesuresProd.csv', sep = ',')
data_time=data_Pro['time']
data_thread=data_Pro['thread']
data_1=data_time[data_thread==1]
data_2=data_time[data_thread==2]
data_3=data_time[data_thread==3]
data_4=data_time[data_thread==4]
#boite à moustache Producteur/Consommateur
fig2=plt.figure()
plt.boxplot([data_2,data_3,data_4], labels=[2,3,4])
plt.ylabel('Time')
plt.title('Box plot Producteur')
plt.show()
plt.close()