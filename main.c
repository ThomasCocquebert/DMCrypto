#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

/*
* Convertit une chaîne de carctère en mpz_t avec la focntion mpz_set_str
* Prend un pointeur de mpz_t et un const char* en entrée
* Renvoie 1 si la chaine de caractère est un nombre valide en base 10 et 0 sinon
*/
int stringToMpz(const char* strNb, mpz_t* nb)
{
	if(mpz_set_str(*nb, strNb,10) == 0) return 1;
	else return 0;
}

/*
* Retourne un nombre aléatoire dans l'intervalle [0,limit-1]
* Prend un mpz_t, un pointeur de mpz_t et un gmp_randstate_t en paramètre
* Renvoie void car la valeur aléatoire est directement stockée dans le pointeur
* Enregistre la valeur du nombre à tester -2 dans subLim
* Ajoute 2 à setNb après tirage du nombre aléatoire pour rester dans l'intervalle [0,limit-1]
*/
void aleaNb(mpz_t limit, mpz_t* setNb, gmp_randstate_t rand)
{
	mpz_t subLim;
	mpz_init(subLim);
	mpz_set(subLim,limit);
	mpz_sub_ui(subLim,subLim,2);
	mpz_urandomm(*setNb,rand,subLim);
	mpz_add_ui(*setNb,*setNb,2);
	mpz_clear(subLim);
}

/*
* Calcule le pgcd de deux mpz_t
* Prend deux mpz_t et un pointeur de mpz_t en paramètre
* Renvoie un void car la valeur du pgcd est djà stockée dans nbPgcd
* Algorithme récursif prit de https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide et transposer à la librairie
*/
void pgcd(mpz_t a, mpz_t b, mpz_t *nbPgcd)
{
	mpz_t reste;
	mpz_init(reste);

	if(mpz_cmp_ui(b,0)==0)
	{
		mpz_set(*nbPgcd,a);
	}
	if(mpz_cmp_ui(b,0)!=0)
	{
		mpz_mod(reste,a,b);

		pgcd(b,reste,nbPgcd);
	}

	mpz_clear(reste);
}

int calcJacobi(mpz_t num, mpz_t den)
{
	return 0;
}

int main(int argc, char** argv)
{
	gmp_randstate_t rand;
	gmp_randinit_mt(rand);

	mpz_t nb,alea,nbPgcd;
	mpz_init(nb);
	mpz_init(alea);
	mpz_init(nbPgcd);
	stringToMpz(argv[1],&nb);
	aleaNb(nb,&alea,rand);
	aleaNb(nb,&alea,rand);
	mpz_out_str(NULL,10,nb);
	printf("\n");
	mpz_out_str(NULL,10,alea);
	printf("\n");
	pgcd(nb,alea,&nbPgcd);
	mpz_out_str(NULL,10,nbPgcd);
	printf("\n");
	mpz_clear(nb);
	mpz_clear(alea);
	mpz_clear(nbPgcd);
	gmp_randclear(rand);
	/*
	if(stringToMpz(argv[1], &nb) == 1)
	{
		printf("Test réussi\n");
		mpz_clear(nb);
		exit(0);
	}
	else
	{
		printf("Echec\n");
		mpz_clear(nb);
		exit(1);
	}
	*/
	exit(0);
}