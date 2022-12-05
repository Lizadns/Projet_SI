import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def moustache(data_name, name):

    data=pd.read_csv(data_name, sep = ',')
    data_time=data['time']
    data_thread=data['thread']

    data_1=data_time[data_thread==1]
    data_2=data_time[data_thread==2]
    data_4=data_time[data_thread==4]
    data_8=data_time[data_thread==8]
    data_16=data_time[data_thread==16]
    data_32=data_time[data_thread==32]
    data_64=data_time[data_thread==64]

    fig=plt.figure()
    plt.boxplot([data_1,data_2,data_4,data_8,data_16,data_32,data_64], labels=[1,2,4,8,16,32,64],showmeans=True)
    plt.ylabel('Temps [s]')
    plt.ylim(bottom=0)
    plt.xlabel('Nombre de thread')
    plt.title('Boite à moustache de ' + name)
    plt.savefig('../Projet_SI/Graphe/'+name+'.png')
    plt.close()

moustache('mesuresEL.csv', "EcrivainsLecteurs")
moustache('mesuresPhilosophe.csv', "Philosophe")
moustache('mesuresProd.csv', "ProducteurConsommateur")
moustache('mesuresTestAndSet.csv', "Test-and-set")
moustache('mesuresTestAndTestAndSet.csv', "Test-and-test-and-set")
moustache('mesuresEL2.csv', "EcrivainsLecteur avec attente active")
moustache('mesuresPC2.csv', "ProducteurConsommateur avec attente active")
moustache('mesuresPhilosophe2.csv', "Philosophe avec attente active")



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