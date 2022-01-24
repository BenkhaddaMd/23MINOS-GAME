#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "modele/structure.h"
#include "modele/modele.h"
#include "vue/vue.h"

int main(int argc, char **argv)
{
    
    int quit = 0;
    ParametresJeu param;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    init_fenetre(&window, &renderer, &texture);

    interface_1(&window, &renderer, &texture);
    //event_interface_1(&window, &renderer, &texture, &param);
    param.estDomino = 1;
    param.nbJoueurs = 3;

    interface_2(&window, &renderer, &texture);
    //event_interface_2(&window, &renderer, &texture, &param);

    if(param.estDomino)
    {
        int gagne = -1, tour;
        int choixDomino, choixEmplacement;
        Domino *pioche;
        JoueurPlateau joueurs[param.nbJoueurs];
        Domino *plateau;

        interface_3(&window, &renderer, &texture, &param);
        event_interface_3(&window, &renderer, &texture, &param, joueurs);

        SDL_RenderClear(renderer);
        melange_dominos(&pioche);
        distribuer_dominos(joueurs, param.nbJoueurs, &pioche);
        plateau = qui_commence(joueurs, param.nbJoueurs, &tour);
        SDL_RenderClear(renderer);
        while(gagne == -1 )
        {
            interface_plateau(&window, &renderer, &texture, &param, joueurs, &plateau, tour);
            event_plateau(&window, &renderer, &texture, &param, joueurs, &plateau, tour, &pioche);
            tour = (tour+1)%param.nbJoueurs;
            SDL_RenderClear(renderer);
            gagne = est_gangne(joueurs ,param); 
        }
    }
    detruie(&window, &renderer, &texture);
    return 0;
}