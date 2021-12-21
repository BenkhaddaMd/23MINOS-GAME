#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include "structure.h"
#include "modele.h"
#include "vue.h"


int main(int argc, char **argv)
{
    Domino dominos[28];
    Domino *pioche;
    JoueurPlateau joueur[3];

    init_dominos(dominos);
    melange_dominos(dominos, &pioche);
    affiche_dominos_melange(pioche);

    distribuer_dominos(joueur, 3, &pioche);
    affiche_joueur(joueur);
    qui_commence(joueur, 3);
    printf("les dominos de jeu \n");
    affiche_joueur(joueur);

    return 0;
}