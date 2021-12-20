#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

// STRUCTURE
typedef struct domino{
    int valeurGauche;
    int valeurDroite;
    struct domino* suivant;
}Domino;

struct triomino{
    int valeurGauche;
    int valeurDroite;
    int valeurCentre;
    struct domino* gauche;
    struct domino* droite;
    struct domino* centre;
};

// MODELE

int alea_int(int N) 
{ 
    static int init_alea = 1;
    if (init_alea) srand(time(NULL));
	init_alea = 0;
	return (int) (N*rand() / RAND_MAX);
}

void init_dominos(Domino *dominos)
{
     int i, j, position=0;
    for(i=6; i>=0; i--)
    {
        for(j=i; j>=0; j--)
        {
            dominos[position].valeurGauche = j;
            dominos[position].valeurDroite = i;
            position++;
        }
    }
}

Domino* melange_dominos(Domino *dominos)
{
    int i, r, pris[28];
    Domino *melangeDominos = NULL, *pointeurPosition;
    for(i=0; i<28; i++)
        pris[i] = 0;

    i=0;
    r = alea_int(28);
    while(i<28)
    {
        r = alea_int(28);   
        if(!pris[r])
        {
            Domino *noeud = malloc(sizeof(Domino));
            noeud->valeurDroite = dominos[r].valeurDroite;
            noeud->valeurGauche = dominos[r].valeurGauche;
            noeud->suivant = NULL;
            if(i==0)
            {
                melangeDominos = noeud;
                pointeurPosition = melangeDominos;
            }
            else
            {
                pointeurPosition->suivant = noeud; 
                pointeurPosition = pointeurPosition->suivant;
            }
            pris[r]=1;
            i++;      
        }
    }
    return melangeDominos;
}

// VUE 
// il s'affiche en console juste pour tester  

void affiche_dominos(Domino *dominos)
{
    int i;
    for(i=0; i<28; i++)
    {
        printf(" [%d | %d] ", dominos[i].valeurGauche,dominos[i].valeurDroite);
    }
}

void affiche_dominos_melange(Domino *dominos)
{
    while(dominos != NULL)
    {
        printf(" [%d | %d] -> ", dominos->valeurGauche,dominos->valeurDroite);
        dominos = dominos->suivant;
    }
    printf("X");
}

int main(int argc, char **argv)
{
    Domino dominos[28];
    Domino *pioche;
    init_dominos(dominos);
    pioche = melange_dominos(dominos);
    affiche_dominos_melange(pioche);
    getchar();
    return 0;
}