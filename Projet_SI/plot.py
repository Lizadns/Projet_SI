import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def plot(data_name, name):

    data=pd.read_csv(data_name, sep = ',')
    data_time=data['time']
    data_thread=data['thread']
    thread=[1,2,4,8,16,32,64]
    mean=[]
    ecart=[]
    for i in thread:
        mean.append(data_time[data_thread==i].mean())
        ecart.append(np.std(data_time[data_thread==i]))

    fig=plt.figure()
    plt.plot(thread,mean,marker = "o", linestyle= "--",markersize = 5, linewidth= 1, color= "royalblue")
    plt.errorbar(thread, mean,yerr=ecart,linestyle = "None",color= "g")
    plt.legend(["moyenne", "ecart type"])
    plt.ylabel('Temps [s]')
    plt.grid(True)
    plt.ylim(bottom=0)
    plt.xlabel('Nombre de thread')
    plt.title('Mesures des performances de ' + name)
    plt.savefig('../Projet_SI/Graphe/'+name+'.png')
    plt.close()


def compare(data_name1, name1, data_name2,name2):

    data1=pd.read_csv(data_name1, sep = ',')
    data_time1=data1['time']
    data_thread1=data1['thread']
    mean1=[]
    ecart1=[]

    data2=pd.read_csv(data_name2, sep = ',')
    data_time2=data2['time']
    data_thread2=data2['thread']
    mean2=[]
    ecart2=[]

    thread=[1,2,4,8,16,32,64]
    for i in thread:
        mean1.append(data_time1[data_thread1==i].mean())
        ecart1.append(np.std(data_time1[data_thread1==i]))

        mean2.append(data_time2[data_thread2==i].mean())
        ecart2.append(np.std(data_time2[data_thread2==i]))

    
    fig=plt.figure()
    plt.plot(thread,mean1,marker = "o", linestyle= "--",markersize = 5, linewidth= 1, color= "royalblue")
    plt.errorbar(thread, mean1,yerr=ecart1,linestyle = "None",color= "g")
    plt.plot(thread,mean2,marker = "o", linestyle= "--",markersize = 5, linewidth= 1, color= "black")
    plt.errorbar(thread, mean2,yerr=ecart2,linestyle = "None",color= "m")
    if(name1=="Test-and-set et Test-and-test-and-set"):
        plt.legend(["moyenne de Test-and-set", "moyenne de Test-and-test-and-set","ecart type Test-and_set","ecart type Test-and-test-and-set"])
    else:
        plt.legend(["moyenne 1", "moyenne 2","ecart type 1","ecart type 2"])
    plt.ylabel('Temps [s]')
    plt.grid(True)
    plt.ylim(bottom=0)
    plt.xlabel('Nombre de thread')
    plt.title('Comparaison des 2 performances de ' + name1)
    plt.savefig('../Projet_SI/Graphe/'+name2+'.png')
    plt.close()

plot('mesuresEL.csv', "EcrivainsLecteurs")
plot('mesuresPhilosophe.csv', "Philosophe")
plot('mesuresPC.csv', "ProducteurConsommateur")
compare('mesuresTas.csv', "Test-and-set et Test-and-test-and-set",'mesuresTatas.csv', "Test-and-test-and-set")
compare('mesuresEL.csv', "EcrivainsLecteurs",'mesuresEL2.csv', "EcrivainsLecteur avec attente active")
compare('mesuresPC.csv', "ProducteurConsommateur",'mesuresPC2.csv', "ProducteurConsommateur avec attente active")
compare('mesuresPhilosophe.csv', "Philosophe",'mesuresPhilosophe2.csv', "Philosophe avec attente active")