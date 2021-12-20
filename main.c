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
    init_dominos(dominos);
    pioche = melange_dominos(dominos);
    affiche_dominos_melange(pioche);
    getchar();
    return 0;
}