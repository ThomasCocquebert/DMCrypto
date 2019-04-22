DM Crypto

Un makefile est à la disposition pour compiler et tester le code.
La description des fonctions est détaillé dans le fichier main.c.
La fonction pour calculer n'a pas été implémenté, la fonction donnée dans la librairie est donc utilisé à la place.

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