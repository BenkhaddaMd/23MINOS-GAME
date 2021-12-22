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
    distribuer_dominos(joueur, 3, &pioche, 5);
    affiche_joueur(joueur);
    qui_commence(joueur, 3, 5);
    affiche_joueur(joueur);
    affiche_dominos_melange(pioche);
  
/*
    SDL_Surface *ecran = NULL;
    SDL_Surface *menu = NULL;
    int continuer = 3;
    SDL_Rect positionMenu;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("link.bmp"), NULL);
    ecran = SDL_SetVideoMode(952, 442, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("23MINOS", NULL);

    menu = IMG_Load("menu_png");
    positionMenu.x = 0;
    positionMenu.y = 0;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            
            default:
                break;
            }
            break;
        
        default:
            break;
        }
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_flip(ecran);
    }
    SDL_FreeSurface(menu);
    SDL_Quit();
      */
    return 0;
}