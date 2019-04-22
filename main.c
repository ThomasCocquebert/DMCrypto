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

/*
* Test le nombre d'argument pour s'assurer du bon nombre
* Renvoie 0 si le nombrd d'argumen est invalide, 1 si seul le chiffre à tester est fourni, et 2 si le nombre
* à tester ET le nombre de répétition du test est donné
*/
int testArg(int argc)
{
	if(argc == 1) return 0;
	if(argc > 3) return 0;
	if(argc == 2) return 1;
	if(argc == 3) return 2;
	return 0;
}

/*
* Calcul l'exposant utilisé dans le Square and Multiply
* Prend un mpz_t et un pointeur de mpz_t en paramètre
* Renvoie void car l'exposant est directement stockée dans *exp
*/
void calcExposant(mpz_t n, mpz_t* exp)
{
	mpz_sub_ui(*exp,n,1);
	mpz_tdiv_q_ui(*exp,*exp,2);
}

//A implémenter
int calcJacobi(mpz_t num, mpz_t den)
{
	/*
	int pow2 = 0;
	mpz_t div2;
	mpz_init(div2);
	*/

	/*
	mpz_mod(num,num,den);
	mpz_out_str(NULL,10,num);
	printf("\n");
	*/
	/*
	mpz_fdiv_q_2exp(div2,num,pow2);
	mpz_out_str(NULL,10,div2);
	printf("\n");
	printf("%d\n",pow2);

	mpz_clear(div2);
	return 0;
	*/
	return mpz_jacobi(num,den);
}

/*
* Square and Multiply
* Prend en paramètre un pointeur mpz_t *a qui représente le nombre mis à a puissance
* Un pounteur mpz_t *h qui représente la valeur de la puissance
* Un mpz_t n qui représente la valeur du modulo
* *a prend directement la valeur de a^h%n à la fin de la fonction
* Tiré de la version itérative de l'algorithme trouvé sur 
* https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Basic_method
*/
void squareMultiply(mpz_t *a, mpz_t *h, mpz_t n)
{
	mpz_t y;
	mpz_init(y);

	if(mpz_cmp_ui(*h,0)==0)
	{
		mpz_set_ui(*a,1);
		return;
	}
	mpz_set_ui(y,1);
	while(mpz_cmp_ui(*h,1))
	{
		if(mpz_even_p(*h))
		{
			mpz_mul(*a,*a,*a);
			mpz_mod(*a,*a,n);
			mpz_tdiv_q_ui(*h,*h,2);
		}
		else
		{
			mpz_mul(y,*a,y);
			mpz_mod(y,y,n);
			mpz_mul(*a,*a,*a);
			mpz_mod(*a,*a,n);
			mpz_sub_ui(*h,*h,1);
			mpz_tdiv_q_ui(*h,*h,2);
		}
	}
	mpz_mul(*a,*a,y);
	mpz_mod(*a,*a,n);
	mpz_clear(y);
}

/*
* Fonction avec un seul paramètre
* Fait 10 fois le teste se Solovay-Strassen par défaut
* Renvoie un int : 0 si le nombre n'est pas premier, 1 si le nombre est probablement premier après 10 itération
* nbJacobi contient le nombre de Jacobi de (a/nbTeste)
* rand contient le nombre aléatoire entre 2 et nbTeste-1
* expo contient la valeur de l'exponentielle utilisé dans Square and Multiply
* nMinus1 contient nbTeste -1 utile pour tester si rand après S&M est égale à -1 mod nbTeste 
*/
int solovayStrassen(mpz_t nbTeste)
{
	int i;
	mpz_t rand, expo, nbJacobi, nMinus1;
	mpz_init(nbJacobi);
	mpz_init(rand);
	mpz_init(expo);
	mpz_init(nMinus1);
	mpz_sub_ui(nMinus1,nbTeste,1);
	gmp_randstate_t seed;
	gmp_randinit_mt(seed);


	for(i=0;i<10;i++)
	{
		aleaNb(nbTeste,&rand,seed);
		printf("Nombre a = ");
		mpz_out_str(NULL,10,rand);
		printf("\n");
		mpz_set_si(nbJacobi,calcJacobi(rand,nbTeste));
		printf("Jacobi de ");
		mpz_out_str(NULL,10,rand);
		printf(" sur ");
		mpz_out_str(NULL,10,nbTeste);
		printf(" = ");
		mpz_out_str(NULL,10,nbJacobi);
		printf("\n \n");
		if(mpz_cmp_ui(nbJacobi,0)==0)
		{
			printf("Le nombre n'est pas premier\n");
			mpz_clear(rand);
			mpz_clear(expo);
			mpz_clear(nMinus1);
			mpz_clear(nbJacobi);
			gmp_randclear(seed);
			return 0;
		}
		calcExposant(nbTeste,&expo);
		printf("Exposant = ");
		mpz_out_str(NULL,10,expo);
		printf("\n");
		squareMultiply(&rand,&expo,nbTeste);
		printf("S&M = ");
		mpz_out_str(NULL,10,rand);
		printf("\n");
		printf("r mod n = ");
		mpz_out_str(NULL,10,nbJacobi);
		printf("\n \n");
		if(mpz_cmp(rand,nbJacobi))
		{
			if(mpz_cmp(rand,nMinus1))
			{
				printf("Le nombre n'est pas premier\n");
				mpz_clear(rand);
				mpz_clear(expo);
				mpz_clear(nMinus1);
				mpz_clear(nbJacobi);
				gmp_randclear(seed);
				return 0;
			}
		}
		
	}
	mpz_clear(rand);
	mpz_clear(expo);
	mpz_clear(nbJacobi);
	mpz_clear(nMinus1);
	gmp_randclear(seed);
	return 1;
}

/*
* Même fonction que  solovayStrassen
* prend int kiteration en paramètre qui définit combien de fois la fonction effectue le test
*/
int solovayStrassenKiteration(unsigned long int kiteration, mpz_t nbTeste)
{
	if(kiteration <= 0)
	{
		printf("Erreur : nombre de teste invalide\n");
		return -1;
	}
	int i;
	mpz_t rand, expo, nbJacobi, nMinus1;
	mpz_init(nbJacobi);
	mpz_init(rand);
	mpz_init(expo);
	mpz_init(nMinus1);
	mpz_sub_ui(nMinus1,nbTeste,1);
	gmp_randstate_t seed;
	gmp_randinit_mt(seed);


	for(i=0;i<kiteration;i++)
	{
		aleaNb(nbTeste,&rand,seed);
		printf("Nombre a = ");
		mpz_out_str(NULL,10,rand);
		printf("\n");
		mpz_set_si(nbJacobi,calcJacobi(rand,nbTeste));
		printf("Jacobi de ");
		mpz_out_str(NULL,10,rand);
		printf(" sur ");
		mpz_out_str(NULL,10,nbTeste);
		printf(" = ");
		mpz_out_str(NULL,10,nbJacobi);
		printf("\n \n");
		if(mpz_cmp_ui(nbJacobi,0)==0)
		{
			printf("Le nombre n'est pas premier\n");
			mpz_clear(rand);
			mpz_clear(expo);
			mpz_clear(nMinus1);
			mpz_clear(nbJacobi);
			gmp_randclear(seed);
			return 0;
		}
		calcExposant(nbTeste,&expo);
		printf("Exposant = ");
		mpz_out_str(NULL,10,expo);
		printf("\n");
		squareMultiply(&rand,&expo,nbTeste);
		printf("S&M = ");
		mpz_out_str(NULL,10,rand);
		printf("\n");
		printf("r mod n = ");
		mpz_out_str(NULL,10,nbJacobi);
		printf("\n \n");
		if(mpz_cmp(rand,nbJacobi))
		{
			if(mpz_cmp(rand,nMinus1))
			{
				printf("Le nombre n'est pas premier\n");
				mpz_clear(rand);
				mpz_clear(expo);
				mpz_clear(nMinus1);
				mpz_clear(nbJacobi);
				gmp_randclear(seed);
				return 0;
			}
		}
		
	}
	mpz_clear(rand);
	mpz_clear(expo);
	mpz_clear(nbJacobi);
	mpz_clear(nMinus1);
	gmp_randclear(seed);
	return 1;
}

int main(int argc, char** argv)
{
	mpz_t premier;
	unsigned long int k;
	mpz_init(premier);
	if(testArg(argc)==1)
	{
		if(stringToMpz(argv[1],&premier))
		{
			printf("10 itérations du test de Solovay Strassen\n");
			if(solovayStrassen(premier)) printf("Le nombre est probablement premier \n");
		}
		else
		{
			printf("Erreur : nombre invalide\n");
			mpz_clear(premier);
			exit(1);
		}
	}
	if(testArg(argc)==2)
	{
		if(stringToMpz(argv[1],&premier))
		{
			k = mpz_get_ui(premier);
		}
		else
		{
			printf("Erreur : nombre invalide\n");
			mpz_clear(premier);
			exit(1);
		}
		if(stringToMpz(argv[2],&premier))
		{
			printf("%ld itérations du test de Solovay-Strassen\n",k);
			if(solovayStrassenKiteration(k,premier)) printf("Le nombre est probablement premier \n");
		}
		else
		{
			printf("Erreur : nombre invalide\n");
			mpz_clear(premier);
			exit(1);
		}
	}
	mpz_clear(premier);
	exit(0);
}