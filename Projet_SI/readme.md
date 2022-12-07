Notre projet est séparé en 2 parties. 
La première correspond à l'implémentation des applications en utilisant les primitives de synchronisation POSIX. Voici les fichiers qui vont seront utiles pour celle-ci:
-Le fichier EcrivainLecteur.c contenant l'implémentation du problème des EcrivainsLecteurs avec priorité aux écrivains.
-Le fichier Philosophe.c contenant l'implémentation du problème des philosophes.
-Le fichier ProducteurConsommateur.c contenant l'implémentation du problème des producteurs et consommateur.

La deuxième partie correspond à l'implémentation des applications en utilisant les primitives de synchronisation par attente active. Voici les fichiers que nous avons implémentés pour celle-ci:
-Le fichier EcrivainLecteur2.c contenant l'adaption de notre EcrivainLecteur.c à l'attente active.
-Le fichier Philosophe2.c contenant l'adaption de notre Philosophe.c à l'attente active.
-Le fichier ProducteurConsommateur2.c contenant l'adaption de notre ProducteurConsommateur.c à l'attente active.
-Le fichier sémaphore.c contenant notre implémentation de l'interface sémaphore sur la base de nos primitives d'attente active.
-Le fichier test_and_set.c contenant notre mis en oeuvre d'un verrou par attente active sur le modèle de l'algorithme test-and-set.
-Le fichier test-and-test-and-set.c contenant l'implémentation d'un nouveau verrou sur le modèle de l'algorithme test-and-test-and-set.
-Le fichier main-test-and-test-and-set.c contenant la fonction de notre test-and-est-and-set ainsi que sa fonction main.

Notre projet comprend également des fichiers headers pour faciliter l'import de certains de nos fichiers dans d'autres.

La commande afin de compiler nos fichiers est : make all
La commande afin de run nos fichiers est : ./nomDonnéDansMakefile $thread et ./nomDonnéDansMakefile $thread $thread pour nos EcrivainsLecteurs.