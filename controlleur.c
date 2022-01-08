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
    /*

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
  
    
   */
    
    int quit = 0;
    ParametresJeu param;
    SDL_Event event;
    SDL_bool passeInterface_2;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Surface * image = IMG_Load("dominos.gif");
    SDL_Texture * texture;
    SDL_Rect position;

    init_fenetre(&window, &renderer, &texture);

    interface_1(&window, &renderer, &texture);
    event_interface_1(&window, &renderer, &texture, &param);

    interface_2(&window, &renderer, &texture);
    event_interface_2(&window, &renderer, &texture, &param);

    if(param.estDomino)
    {
        int termine = 0, tour;
        int choixDomino, choixEmplacement;
        Domino *pioche;
        JoueurPlateau joueurs[4];
        Domino *plateau;

        interface_3(&window, &renderer, &texture, &param);
        event_interface_3(&window, &renderer, &texture, &param, joueurs);

        melange_dominos(&pioche);
        //affiche_dominos_melange(pioche);
        distribuer_dominos(joueurs, param.nbJoueurs, &pioche);
        affiche_joueur(joueurs, param.nbJoueurs);
        plateau = qui_commence(joueurs, param.nbJoueurs, &tour);

        for(int j=0;j<11;j++)
        {ajout_plateau(&plateau, supprime_noeud(&joueurs[tour].liste, 0), 1);
        tour = (tour +1)%param.nbJoueurs;}
        
        interface_plateau(&window, &renderer, &texture, &param, joueurs, plateau);
        //event_plateau(&window, &renderer, &texture, &param, joueurs);
        
        while(1)
        {
            SDL_Event event;
            SDL_WaitEvent(&event);
            if(event.type == SDL_QUIT)
                break;
        }
    }    

    detruie(&window, &renderer, &texture);
    return 0;
}