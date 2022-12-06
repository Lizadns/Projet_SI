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
    mean_1=data_1.mean()
    mean_2=data_2.mean()
    mean_4=data_4.mean()
    mean_8=data_8.mean()
    mean_16=data_16.mean()
    mean_32=data_32.mean()
    mean_64=data_64.mean()
    mean=[mean_1,mean_2,mean_4,mean_8,mean_16,mean_32,mean_64]
    ecart=[np.std(data_1),np.std(data_2),np.std(data_4),np.std(data_8),np.std(data_16),np.std(data_32),np.std(data_64)]
    fig=plt.figure()
    plt.plot([1,2,4,8,16,32,64],mean,marker = "o", linestyle= "--",markersize = 5, linewidth= 1, color= "royalblue")
    plt.errorbar([1,2,4,8,16,32,64], mean,yerr=ecart,linestyle = "None",color= "g")
    plt.legend(["moyenne", "ecart type"])
    plt.ylabel('Temps [s]')
    plt.grid(True)
    plt.ylim(bottom=0)
    plt.xlabel('Nombre de thread')
    plt.title('Mesures des performances de ' + name)
    plt.savefig('../Projet_SI/Graphe/'+name+'.png')
    plt.close()

moustache('mesuresEL.csv', "EcrivainsLecteurs")
moustache('mesuresPhilosophe.csv', "Philosophe")
#moustache('mesuresPC.csv', "ProducteurConsommateur")
moustache('mesuresTas.csv', "Test-and-set")
moustache('mesuresTatas.csv', "Test-and-test-and-set")
moustache('mesuresEL2.csv', "EcrivainsLecteur avec attente active")
#moustache('mesuresPC2.csv', "ProducteurConsommateur avec attente active")
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