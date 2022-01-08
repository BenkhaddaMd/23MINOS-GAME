///////// VUE /////////
#include <string.h>
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

void affiche_joueur(JoueurPlateau *joueur, int nbJoueurs)
{
    for(int k=0; k<nbJoueurs; k++)
    {
        printf("\n Joueur %d : ",k);
        Domino *position = joueur[k].liste;
        while (position != NULL)
        {
            printf(" -> [ %d | %d ]", position->valeurGauche,position->valeurDroite);
            position = position->suivant;
        }
        printf("\n");   
    }
}

SDL_Texture* GetAreaTextrue(SDL_Rect rect, SDL_Renderer* renderer, SDL_Texture* source)
{
  SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);          
  SDL_SetRenderTarget(renderer, result);
  SDL_RenderCopy(renderer, source, &rect, NULL);
  SDL_SetRenderTarget(renderer, NULL);  
  return result;
}

SDL_Texture* affiche_domino(SDL_Renderer* renderer, SDL_Texture *source, int indice)
{
    SDL_Rect rect;
    
    rect.x = 1082 * ( indice /7);  rect.y = 594  *(indice%7);
    rect.w = 1082 ;  rect.h = 594  ;    
    
    return GetAreaTextrue(rect, renderer, source);  
}

void init_fenetre(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture)
{
    SDL_Surface *background;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Rect position;
    position.x = 0;
    position.y = 0; 
    position.w = 1250;
    position.h = 680;
    *window = SDL_CreateWindow("23MINOS",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1250, 680, 0);
    *renderer = SDL_CreateRenderer(*window, -1, 0);
    background = IMG_Load("background.bmp");
    *texture = SDL_CreateTextureFromSurface(*renderer, background);
    SDL_RenderCopy(*renderer, *texture, NULL, &position);
    SDL_RenderPresent(*renderer);
}

void detruie(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture)
{
    SDL_DestroyTexture(*texture);
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}

void interface_1(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture)
{
    SDL_Surface *logo, *domino, *triomino, *bouton; 
    SDL_Rect positionLogo, positionDom, positionTrio, positionBouton;

    positionLogo.x = 10; positionLogo.y = 10; positionLogo.w = 300;   positionLogo.h = 80;
    positionDom.x = 460; positionDom.y = 220; positionDom.w = 120;   positionDom.h = 230;
    positionTrio.x = 540; positionTrio.y = 220; positionTrio.w = 230;   positionTrio.h = 200;
    positionBouton.x = 520; positionBouton.y = 550; positionBouton.w = 200;   positionBouton.h = 65;

    logo = IMG_Load("logo.gif");
    domino = IMG_Load("domino.gif");
    triomino = IMG_Load("triomino.gif");
    bouton = IMG_Load("bouton.gif");

    *texture = SDL_CreateTextureFromSurface(*renderer, logo);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionLogo);
    *texture = SDL_CreateTextureFromSurface(*renderer, domino);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionDom);
    *texture = SDL_CreateTextureFromSurface(*renderer, triomino);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionTrio);
    *texture = SDL_CreateTextureFromSurface(*renderer, bouton);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionBouton);

    SDL_RenderPresent(*renderer);
}

void change_choix(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, int choix)
{
    SDL_Surface *domino, *triomino; 
    SDL_Rect positionDom, positionTrio;

    positionDom.x = 460; positionDom.y = 220; positionDom.w = 120;   positionDom.h = 230;
    positionTrio.x = 540; positionTrio.y = 220; positionTrio.w = 230;   positionTrio.h = 200;

    if(choix)
    {
        domino = IMG_Load("domino.gif");
        *texture = SDL_CreateTextureFromSurface(*renderer, domino);
        SDL_RenderCopy(*renderer, *texture, NULL, &positionDom);
    }
    else
    {
        triomino = IMG_Load("triomino.gif");
        *texture = SDL_CreateTextureFromSurface(*renderer, triomino);
        SDL_RenderCopy(*renderer, *texture, NULL, &positionTrio);
    }
    SDL_RenderPresent(*renderer);
}

int estTriom(SDL_Point clic)
{
        SDL_Point sommetTrio;

        int base,hauteurTrio;
        base = 230; hauteurTrio = 200; 
        
        sommetTrio.x=655;sommetTrio.y=220;

        if((clic.y >= sommetTrio.y)&&(clic.y<=(sommetTrio.y + hauteurTrio)))
        {	
            if(abs(((float)(base)/(2*hauteurTrio))*(sommetTrio.y-clic.y))>=abs((float)(clic.x)-(sommetTrio.x)))
                return 1;
        }			
        return 0;    
}

int estDom(SDL_Point clic)
{
        SDL_Rect rectDom;

        rectDom.x = 460; rectDom.y = 220; rectDom.w = 120;   rectDom.h = 230;
		
        if(SDL_PointInRect(&clic,&rectDom))
            return 1;
        return 0;
}

int estSuivant_1(SDL_Point clic)
{
        SDL_Rect rec;
        rec.x = 520; rec.y = 550; 
        rec.w = 200;   rec.h = 65;
		
        if(SDL_PointInRect(&clic,&rec))
            return 1;
        return 0;
}

void event_interface_1(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture,ParametresJeu *param)
{
    SDL_Point p;
    SDL_Event event;
    int quit = 0;
    param->estDomino = 0;
    param->estTriomino = 1;
    while(!quit)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT)
            quit = 1;
        p.x = event.button.x;
        p.y = event.button.y;
        if(event.button.clicks >= 1)
        {
            if (estTriom(p) && !estDom(p))
            {
                param->estTriomino = 1;
                param->estDomino = 0;
            }
            else if(!estTriom(p) && estDom(p))
            {   
                param->estDomino = 1;
                param->estTriomino = 1;
            }
            change_choix(window, renderer, texture,param->estDomino);
            if(estSuivant_1(p))
                break;
        }
        if(quit)
            detruie(window, renderer, texture);
    }           
}

int nbJoueurs(SDL_Point clic)
{
    SDL_Rect r1, r2, r3, r4;

    r1.x = 230;   r1.y = 280;   r1.w = 163;   r1.h = 132;
    r2.x = 433;   r2.y = 280;   r2.w = 163;   r2.h = 132;
    r3.x = 654;   r3.y = 280;   r3.w = 163;   r3.h = 132;
    r4.x = 860;   r4.y = 280;   r4.w = 163;   r4.h = 132;

    if(SDL_PointInRect(&clic, &r1))
        return 1;
    else if(SDL_PointInRect(&clic, &r2))
        return 2;
    else if(SDL_PointInRect(&clic, &r3))
        return 3;
    else if(SDL_PointInRect(&clic, &r4))
        return 4;
}

void change_choix_nombre(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, int nombre)
{
    SDL_Surface *image; 
    SDL_Rect position;
    image = IMG_Load("position.gif");
    *texture = SDL_CreateTextureFromSurface(*renderer, image);
    position.x = (nombre-1)*210 + 280; position.y = 190; position.w = 70;   position.h = 70;
    SDL_RenderCopy(*renderer, *texture, NULL, &position);
    SDL_RenderPresent(*renderer);
}

void interface_2(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture)
{
    SDL_Surface *logo, *choix, *bouton; 
    SDL_Rect positionLogo, positionChoix, positionBouton;

    positionLogo.x = 10; positionLogo.y = 10; positionLogo.w = 300;   positionLogo.h = 80;
    positionChoix.x = 130; positionChoix.y = 100; positionChoix.w = 970;   positionChoix.h = 500;
    positionBouton.x = 520; positionBouton.y = 550; positionBouton.w = 200;   positionBouton.h = 65;

    logo = IMG_Load("logo.gif");
    choix = IMG_Load("nombre_joueurs.gif");
    bouton = IMG_Load("bouton.gif");

    *texture = SDL_CreateTextureFromSurface(*renderer, logo);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionLogo);
    *texture = SDL_CreateTextureFromSurface(*renderer, choix);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionChoix);
    *texture = SDL_CreateTextureFromSurface(*renderer, bouton);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionBouton);

    SDL_RenderPresent(*renderer);
}


void event_interface_2(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, ParametresJeu *param)
{
    SDL_Point p;
    SDL_Event event;
    int quit = 0;
    param->nbJoueurs = 0;
    while(!quit)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT)
            quit = 1;
        p.x = event.button.x;
        p.y = event.button.y;
        if(event.button.clicks >= 1)
        {
            if(nbJoueurs(p))
            {
                param->nbJoueurs = nbJoueurs(p);
                interface_2(window, renderer, texture);
                change_choix_nombre(window, renderer, texture, param->nbJoueurs);
            } 
            else if( estSuivant_1(p) && param->nbJoueurs)
                break;
        }
        if(quit)
            detruie(window, renderer, texture);
    }
}

void get_text_and_rect(SDL_Renderer **renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture) 
{
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(*renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
}

void affiche_text(SDL_Renderer **renderer, SDL_Window **window, SDL_Texture **texture, char *text, SDL_Rect rect)
{
    rect.x += 20;   rect.y += 20;   
    rect.w = 20*strlen(text);  rect.h -= 50;
    TTF_Font *font = TTF_OpenFont("Sans.ttf", 400);
    get_text_and_rect(renderer, 0, 0, text, font, texture);
    SDL_RenderCopy(*renderer, *texture, NULL, &rect);
    SDL_RenderPresent(*renderer);
}

void interface_3(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, ParametresJeu *param)
{
    SDL_Surface *logo, *choix, *bouton, *input; 
    SDL_Rect positionLogo, positionChoix, positionBouton, rectTexte;
    int nb = 0;
    char *nomParDefaut[4] = {"joueur 1","joueur 2","joueur 3","joueur 4"};

    positionLogo.x = 10; positionLogo.y = 10; positionLogo.w = 300;   positionLogo.h = 80;
    positionChoix.x = 130; positionChoix.y = 100; positionChoix.w = 970;   positionChoix.h = 500;
    positionBouton.x = 520; positionBouton.y = 550; positionBouton.w = 200;   positionBouton.h = 65;

    rectTexte.x = 230; rectTexte.y = 217; rectTexte.w = 323;   rectTexte.h = 85;
    input = IMG_Load("input.gif"); 
    logo = IMG_Load("logo.gif");
    choix = IMG_Load("noms_joueurs.gif");
    bouton = IMG_Load("bouton.gif");

    *texture = SDL_CreateTextureFromSurface(*renderer, logo);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionLogo);
    *texture = SDL_CreateTextureFromSurface(*renderer, choix);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionChoix);
    *texture = SDL_CreateTextureFromSurface(*renderer, bouton);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionBouton);
    
    while(nb < param->nbJoueurs)
    {
        rectTexte.x = 230 + 436*(nb%2); rectTexte.y = 217 + 183*(nb/2);
        *texture = SDL_CreateTextureFromSurface(*renderer, input);
        SDL_RenderCopy(*renderer, *texture, NULL, &rectTexte);
        affiche_text(renderer, window, texture, nomParDefaut[nb], rectTexte);
        nb++;
    }
    SDL_RenderPresent(*renderer);
}

void efface_nom_par_defaut(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture ,int indiceJ, int background)
{
    SDL_Rect rectTexte;
    SDL_Surface *input;
    rectTexte.w = 323;   rectTexte.h = 85;
    rectTexte.x = 230 + 436*(indiceJ %2); rectTexte.y = 217 + 183*(indiceJ/2);
    if(background)
        input = IMG_Load("input.gif");
    else
        input = IMG_Load("input_insert.gif");
    *texture = SDL_CreateTextureFromSurface(*renderer, input);
    SDL_RenderCopy(*renderer, *texture, NULL, &rectTexte);
    SDL_RenderPresent(*renderer);    
}

void event_texte(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture , int indiceJ, char *texte)
{
    int quit = 0;
    SDL_Event eventK;
    int i=0;
    char input;
    SDL_Rect rectTexte;
    rectTexte.w = 323;                      rectTexte.h = 85;
    rectTexte.x = 230 + 436*(indiceJ %2);   rectTexte.y = 217 + 183*(indiceJ/2);
    
    while (!quit)
    {
        SDL_PollEvent(&eventK);
        input = ((int)eventK.key.keysym.sym);
        switch( eventK.type ){
                    case SDL_KEYDOWN:
                        if(input >= 97 && input <= 122 && i < 14)
                        {
                            texte[i] = input;
                            texte[ ++i] = '\0';
                        }
                        else if(eventK.key.keysym.sym == SDLK_BACKSPACE && i > 0)
                        {
                            texte[--i] = '\0';
                            SDL_Delay(100);
                        }
                        else if(eventK.key.keysym.sym == SDLK_RETURN)
                            {
                                efface_nom_par_defaut(window,renderer,texture,indiceJ, 1);
                                return;
                            }
                        efface_nom_par_defaut(window,renderer,texture,indiceJ, 0);
                        if(i)
                            affiche_text(renderer, window, texture, texte, rectTexte);
                    break;
                    case SDL_QUIT:
                        quit = 1;
                        break;
            }
        if(quit)
            detruie(window, renderer, texture);
    }
}

void event_interface_3(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, ParametresJeu *param, JoueurPlateau *joueurs)
{
    SDL_Point p;
    SDL_Event event;
    SDL_Rect rectTexte;
    char *texte = NULL;
    rectTexte.w = 323;   rectTexte.h = 85;
    int quit = 0, nb = 0;

    while(!quit)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT)
            quit = 1;
        p.x = event.button.x;
        p.y = event.button.y;
        if(event.button.clicks >= 1)
        {
            nb=0;
            while(nb < param->nbJoueurs)
            {
                rectTexte.x = 230 + 436*(nb%2); rectTexte.y = 217 + 183*(nb/2);
                if(SDL_PointInRect(&p, &rectTexte))
                {
                    texte = malloc(sizeof(char)*15);
                    efface_nom_par_defaut(window,renderer,texture,nb, 0);
                    event_texte(window, renderer, texture, nb, texte);
                    affiche_text(renderer, window, texture, texte, rectTexte);
                    Joueur *j = malloc(sizeof(Joueur));
                    j->nom = texte;
                    j->score = 0;
                    joueurs[nb].infos = j;
                } 
                nb++;  
            }
            if(estSuivant_1(p) && texte != NULL)
                break;
        }
        if(quit)
            detruie(window, renderer, texture);
    }
}

void interface_plateau(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, ParametresJeu *param, JoueurPlateau *joueurs, Domino *plateau)
{
    SDL_Surface *background, *barVertical, *barHorizontal, *dominos; 
    SDL_Rect positionVertical, positionHorizontal, position, positionDomino;
    SDL_Texture *source;
    
    positionVertical.x = 110;   positionVertical.y = 10;    positionVertical.w = 1040;  positionVertical.h = 100;
    positionHorizontal.x = 10;  positionHorizontal.y = 10;  positionHorizontal.w = 100; positionHorizontal.h = 660;
    positionDomino.x = 15;  positionDomino.y = 20;    
    positionDomino.w = 90;  positionDomino.h = 45;
    position.x = 0;     position.y = 0;    
    position.w = 1250;  position.h = 680;
 
    background = IMG_Load("background.bmp"); 
    barVertical = IMG_Load("barVertical.gif");
    barHorizontal = IMG_Load("barHorizontal.gif"); 
    dominos = IMG_Load("dominos.gif"); 

    *texture = SDL_CreateTextureFromSurface(*renderer, background);
    SDL_RenderCopy(*renderer, *texture, NULL, &position);
    *texture = SDL_CreateTextureFromSurface(*renderer, barVertical);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionVertical);
    positionVertical.y = 570;
    *texture = SDL_CreateTextureFromSurface(*renderer, barVertical);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionVertical);

    *texture = SDL_CreateTextureFromSurface(*renderer, barHorizontal);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionHorizontal);
    positionHorizontal.x = 1150;
    *texture = SDL_CreateTextureFromSurface(*renderer, barHorizontal);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionHorizontal);

    source = SDL_CreateTextureFromSurface(*renderer, dominos);
    int indice;
    Domino *p;
    for(int k=0; k < param->nbJoueurs; k++)
    {
        if(k==0)   
        {   
            positionDomino.x = 15; positionDomino.y = 25; 
        }
        if(k==1)   
        {   
            positionDomino.x = 1155; positionDomino.y = 25; 
        }
        else if(k==2)
        {
            positionDomino.x = 115;   positionDomino.y = 15;
        }
        p = joueurs[k].liste;
        while (p != NULL)
        {
            switch (p->valeurGauche)
            {
            case 0:
                indice = p->valeurDroite;
                break;
             case 1:
                indice = 6 + p->valeurDroite;
                break;
             case 2:
                indice = 11 + p->valeurDroite;
                break;
             case 3:
                indice = 15 + p->valeurDroite;
                break;
             case 4:
                indice = 18 + p->valeurDroite;
                break;
             case 5:
                indice = 20 + p->valeurDroite;
                break;
             case 6:
                indice = 27;
                break;
            }
            *texture = affiche_domino(*renderer, source, indice);
            SDL_RenderCopy(*renderer, *texture, NULL, &positionDomino);
            if(k==0 || k==1)
                positionDomino.y += 50;
            else if(k==2 || k==3)
                positionDomino.x += 95;
            p = p->suivant;
        }
    }

    p = plateau;
    positionDomino.x = 300;
    positionDomino.y = 200;
    while (p != NULL)
    {
        switch (p->valeurGauche)
        {
            case 0:
                indice = p->valeurDroite;
                break;
            case 1:
                indice = 6 + p->valeurDroite;
                break;
            case 2:
                indice = 11 + p->valeurDroite;
                break;
            case 3:
                indice = 15 + p->valeurDroite;
                break;
            case 4:
                indice = 18 + p->valeurDroite;
                break;
            case 5:
                indice = 20 + p->valeurDroite;
                break;
            case 6:
                indice = 27;
            break;
        }
        *texture = affiche_domino(*renderer, source, indice);
        SDL_RenderCopy(*renderer, *texture, NULL, &positionDomino);
        positionDomino.x += 100;
        p = p->suivant;
    }

    SDL_RenderPresent(*renderer);
}