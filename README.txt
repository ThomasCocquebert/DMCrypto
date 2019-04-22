DMCrypto

Par Thomas COCQUEBERT
Nr Etudiant 21600767

Un makefile est à la disposition pour compiler et tester le code.
La description des fonctions est détaillé dans le fichier main.c.
La fonction pour calculer le symbole de Jacobi n'a pas été implémentée, la fonction donnée dans la librairie est donc utilisée à la place. Néanmoins, vous retrouverer le code commenté dans le main.c.

Le programme s'appelle par ./solostrass et prend un ou deux paramètres
- Si un seul paramètre est renseigné, alors ce paramètre sera le nombre à tester. De bases le nombre est testé dix fois
- Si deux paramètres sont renseignés, alors le premier sera le nombre d'itération du test de Solovay-Strassen à effectuer et le second le nombre à tester

CODE D'ERREURS:
0 : aucune erreurs, le programme s'est achevé correctement;
1: un des nombres saisies est invalide
2: le nombre à tester à une valeur inferieur à 3
3: trop de paramètre ont été saisi

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