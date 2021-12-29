#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "modele/structure.h"
#include "modele/modele.h"
#include "vue/vue.h"

int main(int argc, char **argv)
{
    int termine = 0, tour;
    int choixDomino, choixEmplacement;
    Domino *pioche;
    JoueurPlateau joueur[2];
    Domino *plateau;
    
    melange_dominos(&pioche);
    affiche_dominos_melange(pioche);
    distribuer_dominos(joueur, 2, &pioche);
    affiche_joueur(joueur, 2);
    plateau = qui_commence(joueur, 2, &tour);
    affiche_joueur(joueur, 2);
    affiche_dominos_melange(pioche);

    while(!termine)
    {
        printf("######## | Jouer | ########\n");
        printf("#%d Jouer \n", tour);
        affiche_dominos_melange(plateau);

        printf(" - les choix : ");
        scanf("%d%d", &choixDomino, &choixEmplacement);
        
        ajout_plateau(&plateau, supprime_noeud(&joueur[tour].liste, choixDomino), choixEmplacement);
        affiche_joueur(joueur, 2);

        tour = (tour+1) % 2;
    }
  
    
   /*
    int quit = 0;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 580, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = IMG_Load("image.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect position;
    position.x = 80;
    position.y = 0;
    position.w = 569;
    position.h = 512;

    while (!quit)
    {
       SDL_WaitEvent(&event);

       switch(event.type)
       {
       case SDL_QUIT:
           quit = 1;
           break;
       }
       SDL_RenderCopy(renderer, texture, NULL, &position);
       SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    */
    return 0;
}