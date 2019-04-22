DMCrypto

Un makefile est à la disposition pour compiler et tester le code.
La description des fonctions est détaillé dans le fichier main.c.
La fonction pour calculer le symbole de Jacobi n'a pas été implémentée, la fonction donnée dans la librairie est donc utilisée à la place.

Le programme s'appelle par ./solostrass et prend un ou deux paramètres
- Si un seul paramètre est renseigné, alors ce paramètre sera le nombre à tester. De bases le nombre est tester dix fois
- Si deux paramètres sont renseignés, alors le premier sera le nombre d'itération du test de Solovay-Strassen à effectuer et le second le nombre à tester

POUR COMPILER:
gcc main.c -Wall -lgmp -o solotrass

OU

make solostrass

OU 

make





POUR TESTER:
./solostrass nb_à_tester

OU

./solostrass nb_de_repetition nb_à_tester

OU

make test

OU

make testk




POUR TESTER LES FUITES MEMOIRES:
make memCheck

OU

make memCheckk




DIVERS:
Pour supprimer l'exécutable:
make clean

Pour indenter le code:
make indent