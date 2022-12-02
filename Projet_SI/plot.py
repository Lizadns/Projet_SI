import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def moustache1(data_name, name):

    data=pd.read_csv(data_name, sep = ',')
    data_time=data['time']
    data_thread=data['thread']

    data_1=data_time[data_thread==1]
    data_2=data_time[data_thread==2]
    data_3=data_time[data_thread==3]
    data_4=data_time[data_thread==4]
    data_5=data_time[data_thread==5]
    data_6=data_time[data_thread==6]

    fig=plt.figure()
    plt.boxplot([data_1,data_2,data_3,data_4,data_5,data_6], labels=[1,2,3,4,5,6])
    plt.ylabel('Temps [s]')
    plt.xlabel('Nombre de thread')
    plt.title('Box plot ' + name)
    plt.savefig('../Projet_SI/Projet_SI/Graphe/'+name+'.png')
    plt.close()

def moustache(data_name, name):

    data=pd.read_csv(data_name, sep = ',')
    data_time=data['time']
    data_thread=data['thread']

    data_2=data_time[data_thread==2]
    data_3=data_time[data_thread==3]
    data_4=data_time[data_thread==4]
    data_5=data_time[data_thread==5]
    data_6=data_time[data_thread==6]

    fig=plt.figure()
    plt.boxplot([data_2,data_3,data_4,data_5,data_6], labels=[2,3,4,5,6])
    plt.ylabel('Temps [s]')
    plt.xlabel('Nombre de thread')
    plt.title('Box plot ' + name)
    plt.savefig('../Projet_SI/Projet_SI/Graphe/'+name+'.png')
    plt.close()

moustache1('../Projet_SI/Projet_SI/mesuresEL.csv', "EcrivainsLecteurs")
moustache('../Projet_SI/Projet_SI/mesuresPhilosophe.csv', "Philosophe")
moustache1('../Projet_SI/Projet_SI/mesuresProd.csv', "ProducteurConsommateur")



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