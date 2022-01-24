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

SDL_Texture* affiche_domino_horizentale(SDL_Renderer* renderer, SDL_Texture *source, int indice)
{
    SDL_Rect rect;
    
    rect.x = 332 * ( indice / 7);  rect.y = 182  *(indice % 7);
    rect.w = 332 ;  rect.h = 182 ;    
    
    return GetAreaTextrue(rect, renderer, source);  
}
SDL_Texture* affiche_domino_verticale(SDL_Renderer* renderer, SDL_Texture *source, int indice)
{
    SDL_Rect rect;
    
    rect.x = 182  *(indice % 7);  rect.y= 332 * ( indice / 7) ;
    rect.w = 182 ;  rect.h = 332 ;    
    
    return GetAreaTextrue(rect, renderer, source);  
}


void init_fenetre(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture)
{
    SDL_Surface *background, *icon;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Rect position;
    position.x = 0;
    position.y = 0; 
    position.w = 1250;
    position.h = 680;
    icon = IMG_Load("assets\\image\\icon.gif");
    *window = SDL_CreateWindow("23MINOS",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1250, 680, 0);
    SDL_SetWindowIcon(*window, icon);
    *renderer = SDL_CreateRenderer(*window, -1, 0);
    background = IMG_Load("assets\\image\\background.bmp");
    *texture = SDL_CreateTextureFromSurface(*renderer, background);
    SDL_RenderCopy(*renderer, *texture, NULL, &position);
    SDL_RenderPresent(*renderer);
    SDL_FreeSurface(background);
    SDL_FreeSurface(icon);
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

    logo = IMG_Load("assets\\image\\logo.gif");
    domino = IMG_Load("assets\\image\\domino.gif");
    triomino = IMG_Load("assets\\image\\triomino.gif");
    bouton = IMG_Load("assets\\image\\bouton.gif");

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
        domino = IMG_Load("assets\\image\\domino.gif");
        *texture = SDL_CreateTextureFromSurface(*renderer, domino);
        SDL_RenderCopy(*renderer, *texture, NULL, &positionDom);
    }
    else
    {
        triomino = IMG_Load("assets\\image\\triomino.gif");
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
    image = IMG_Load("assets\\image\\position.gif");
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

    logo = IMG_Load("assets\\image\\logo.gif");
    choix = IMG_Load("assets\\image\\nombre_joueurs.gif");
    bouton = IMG_Load("assets\\image\\bouton.gif");

    *texture = SDL_CreateTextureFromSurface(*renderer, logo);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionLogo);
    *texture = SDL_CreateTextureFromSurface(*renderer, choix);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionChoix);
    *texture = SDL_CreateTextureFromSurface(*renderer, bouton);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionBouton);

    SDL_RenderPresent(*renderer);
    SDL_FreeSurface(logo);
    SDL_FreeSurface(choix);
    SDL_FreeSurface(bouton);
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

void get_text_and_rect(SDL_Renderer **renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Color textColor) 
{
    int text_width;
    int text_height;
    SDL_Surface *surface;

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(*renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
}

void affiche_text(SDL_Renderer **renderer, SDL_Window **window, SDL_Texture **texture, char *text, SDL_Rect rect, SDL_Color textColor)
{
    rect.x += 20;   rect.y += 20;   
    rect.w = 20*strlen(text);  rect.h -= 50;
    TTF_Font *font = TTF_OpenFont("Sans.ttf", 200);
    get_text_and_rect(renderer, 0, 0, text, font, texture, textColor);
    SDL_RenderCopy(*renderer, *texture, NULL, &rect);
}

void affiche_nom(SDL_Renderer **renderer, SDL_Window **window, SDL_Texture **texture, char *text, SDL_Rect rect, SDL_Color textColor)
{
    rect.w = 10*strlen(text);
    rect.x+=(9-strlen(text))*6;
    TTF_Font *font = TTF_OpenFont("Sans.ttf", 200);
    get_text_and_rect(renderer, 0, 0, text, font, texture, textColor);
    SDL_RenderCopy(*renderer, *texture, NULL, &rect);
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
    input = IMG_Load("assets\\image\\input.gif"); 
    logo = IMG_Load("assets\\image\\logo.gif");
    choix = IMG_Load("assets\\image\\noms_joueurs.gif");
    bouton = IMG_Load("assets\\image\\bouton.gif");

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
        affiche_text(renderer, window, texture, nomParDefaut[nb], rectTexte,(SDL_Color){0, 0, 0, 0});
        SDL_RenderPresent(*renderer);

        nb++;
    }
    SDL_RenderPresent(*renderer);
    SDL_FreeSurface(input);
    SDL_FreeSurface(logo);
    SDL_FreeSurface(choix);
    SDL_FreeSurface(bouton);
}

void efface_nom_par_defaut(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture ,int indiceJ, int background)
{
    SDL_Rect rectTexte;
    SDL_Surface *input;
    rectTexte.w = 323;   rectTexte.h = 85;
    rectTexte.x = 230 + 436*(indiceJ %2); rectTexte.y = 217 + 183*(indiceJ/2);
    if(background)
        input = IMG_Load("assets\\image\\input.gif");
    else
        input = IMG_Load("assets\\image\\input_insert.gif");
    *texture = SDL_CreateTextureFromSurface(*renderer, input);
    SDL_RenderCopy(*renderer, *texture, NULL, &rectTexte);
    SDL_RenderPresent(*renderer);    
    SDL_FreeSurface(input);
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
                        if(input >= 97 && input <= 122 && i < 9)
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
                        {
                            affiche_text(renderer, window, texture, texte, rectTexte, (SDL_Color){0, 0, 0, 0});
                            SDL_RenderPresent(*renderer);
                        }
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
                    affiche_text(renderer, window, texture, texte, rectTexte, (SDL_Color){0, 0, 0, 0});
                    SDL_RenderPresent(*renderer);
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

int indice_domino(Domino *liste)
{
    int indice, gauche, droite;
    Domino *p;
    p = liste;

            if(p->valeurDroite >= p->valeurGauche)
            {
                gauche = p->valeurGauche;
                droite = p->valeurDroite;
            }
            else
            {
                droite = p->valeurGauche;
                gauche = p->valeurDroite;
            }
                switch (gauche)
                {
                case 0:
                    indice = droite;
                    break;
                case 1:
                    indice = 6 + droite;
                    break;
                case 2:
                    indice = 11 + droite;
                    break;
                case 3:
                    indice = 15 + droite;
                    break;
                case 4:
                    indice = 18 + droite;
                    break;
                case 5:
                    indice = 20 + droite;
                    break;
                case 6:
                    indice = 27;
                    break;
                }
    return indice;
}

void affiche_dominos_plateau(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, Domino **plateau)
{
    SDL_Surface *dominos, *dominosInverse, *racourcie; 
    SDL_Rect positionDomino;
    SDL_Texture *source, *racourcieText;
    positionDomino.w = 90;  positionDomino.h = 45;

    dominos = IMG_Load("assets\\image\\dominos.gif");
    source = SDL_CreateTextureFromSurface(*renderer, dominos);
    racourcie = IMG_Load("assets\\image\\racourcie.gif");
    racourcieText = SDL_CreateTextureFromSurface(*renderer, racourcie);
    
    int indice, i=0;
    Domino *p = *plateau;
    positionDomino.x = 150;
    positionDomino.y = 120;
    while (p != NULL)
    {p = p->suivant; i++;}
    p = *plateau;
    while (p != NULL)
    {
        
        if(i==7)
        {
            actualise_plateau(plateau);
            i=2;
            p = *plateau;
        }
        indice = indice_domino(p);
        *texture = affiche_domino_horizentale(*renderer, source, indice);
        if(p->valeurDroite == 7)
        {
           *texture = SDL_CreateTextureFromSurface(*renderer, racourcie);
            SDL_RenderCopy(*renderer, *texture, NULL, &positionDomino);  
        }
        if(!(p->valeurDroite >= p->valeurGauche))
            SDL_RenderCopy(*renderer, *texture, NULL, &positionDomino);
        else
            SDL_RenderCopyEx(*renderer,*texture, NULL,&positionDomino, 180.0f, NULL,SDL_FLIP_NONE);
        positionDomino.x += 90;
        p = p->suivant; 
    }
    SDL_RenderPresent(*renderer);
    SDL_FreeSurface(dominos);
    SDL_FreeSurface(dominosInverse);
}

void interface_plateau(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, ParametresJeu *param, JoueurPlateau *joueurs, Domino **plateau, int tour)
{
    SDL_Surface *background, *barVertical, *barHorizontal, *dominos, *dominosInverse, *pioche, *avatar , *direction; 
    SDL_Rect positionNom, positionVertical, positionHorizontal, position, positionDomino, positionPioche, positionAvatar,positionDominoVerticale, positionDirection;
    SDL_Texture *source,*sourceInverse;
    
    positionVertical.x = 110;   positionVertical.y = 10;    positionVertical.w = 1040;  positionVertical.h = 100;
    positionHorizontal.x = 10;  positionHorizontal.y = 10;  positionHorizontal.w = 100; positionHorizontal.h = 660;
    positionDomino.x = 15;      positionDomino.y = 20;      positionDomino.w = 90;      positionDomino.h = 45;
    positionDominoVerticale.x = 135;   positionDominoVerticale.y = 55;      positionDominoVerticale.w = 40;      positionDominoVerticale.h = 85;
    position.x = 0;             position.y = 0;             position.w = 1250;          position.h = 680;
    positionPioche.x = 125;      positionPioche.y = 515;      positionPioche.w = 90;      positionPioche.h = 45;
    positionDirection.x = 225;      positionDirection.y = 515;      positionDirection.w = 90;      positionDirection.h = 45;
    positionAvatar.w = 45;      positionAvatar.h = 57;

    background = IMG_Load("assets\\image\\background.bmp"); 
    barVertical = IMG_Load("assets\\image\\barVertical.gif");
    barHorizontal = IMG_Load("assets\\image\\barHorizontal.gif"); 
    dominos = IMG_Load("assets\\image\\dominos.gif");
    pioche = IMG_Load("assets\\image\\pioche.gif"); 
    direction = IMG_Load("assets\\image\\direction.gif"); 
    avatar = IMG_Load("assets\\image\\avatar.gif"); 

    *texture = SDL_CreateTextureFromSurface(*renderer, background);
    SDL_RenderCopy(*renderer, *texture, NULL, &position);
    *texture = SDL_CreateTextureFromSurface(*renderer, pioche);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionPioche);
     *texture = SDL_CreateTextureFromSurface(*renderer, direction);
    SDL_RenderCopy(*renderer, *texture, NULL, &positionDirection);
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
    if(tour==0)   
        {   
            positionAvatar.x = 40;      positionAvatar.y = 570;
        }
    if(tour==2)   
        {
            positionAvatar.x = 1180;      positionAvatar.y = 570;
        }
    else if(tour==1)
        {
            positionAvatar.x = 1070;      positionAvatar.y = 20;
        }
    else if(tour==3)
        {
            positionAvatar.x = 1070;      positionAvatar.y = 580;
        }
        *texture = SDL_CreateTextureFromSurface(*renderer, avatar);
        SDL_RenderCopy(*renderer, *texture, NULL, &positionAvatar);

    int indice;
    Domino *p;
    for(int k=0; k < param->nbJoueurs; k++)
    {
        if(k==0)   
        {   
            positionDomino.x = 15; positionDomino.y = 25;
        }
        if(k==2)   
        {
            positionDomino.x = 1155; positionDomino.y = 25;
        }
        else if(k==1)
        {
            positionDomino.x = 105;   positionDomino.y = 37;
        }
        else if(k==3)
        {
            positionDomino.x = 105;   positionDomino.y = 597;
        }
        p = joueurs[k].liste;
        while (p != NULL)
        {
            indice = indice_domino(p);   
            
            if(k==0 || k==2)
            { 
                *texture = affiche_domino_horizentale(*renderer, source, indice);
                SDL_RenderCopy(*renderer, *texture, NULL, &positionDomino);
                positionDomino.y += 50;
                
            } 
            else if(k==1 || k==3)
            {
                *texture = affiche_domino_horizentale(*renderer, source, indice);
                SDL_RenderCopyEx(*renderer,*texture, NULL,&positionDomino, 90.0f, NULL,SDL_FLIP_NONE);
                positionDomino.x += 50;
            }
            p = p->suivant;  
            
        }
    }

    affiche_dominos_plateau(window, renderer, texture, plateau);
    positionNom.w = 90;     positionNom.h = 20;
    positionNom.x = 15;     positionNom.y = 630;
    for(int k=0; k < param->nbJoueurs; k++) 
    {
        if(k==1) 
            {positionNom.x = 1040; positionNom.y = 80;}
        if(k==2)
            {positionNom.x = 1155; positionNom.y = 630;}
        if(k==3)
            {positionNom.x = 1040; positionNom.y = 640;}
        affiche_nom(renderer, window, texture, joueurs[k].infos->nom, positionNom, (SDL_Color){255, 255, 255, 255});
    }

    SDL_RenderPresent(*renderer);
    SDL_FreeSurface(background);
    SDL_FreeSurface(barVertical);
    SDL_FreeSurface(barHorizontal);
    SDL_FreeSurface(dominos);
}

void event_plateau(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture,ParametresJeu *param ,JoueurPlateau *joueurs,Domino **plateau, int tour, Domino **pioche)
{
    SDL_Point p;
    SDL_Event event;
    SDL_Rect rectDomino, positionPioche, positionPasse , positionDirection;
    Domino *pointeurListe;
    int quit = 0, termine = 0, nb, indiceDomino, estPioche = 0, direction = -1;

    positionPioche.x = 125;      positionPioche.y = 515;      positionPioche.w = 45;      positionPioche.h = 45;
    positionPasse.x = 170;       positionPasse.y = 515;       positionPasse.w = 45;       positionPasse.h = 45;
    positionDirection.x = 225;      positionDirection.y = 515;      positionDirection.w = 90;      positionDirection.h = 45;
    Domino *position = *plateau, *domino_a_jouer;

    while(!quit)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT)
            quit = 1;
        p.x = event.button.x;
        p.y = event.button.y;
        if(event.button.clicks >= 1)
        {
            if(tour==0)   
            {   
                rectDomino.x = 15;      rectDomino.y = 25;  rectDomino.w = 90; rectDomino.h = 50;
            }
            else if(tour==2)   
            {   
                rectDomino.x = 1155;    rectDomino.y = 25;  rectDomino.w = 90; rectDomino.h = 50;
            }
            else if(tour==1)
            {
                rectDomino.x = 125;     rectDomino.y = 17;  rectDomino.w = 50; rectDomino.h = 90;
            }
            else if(tour==3)
            {
                rectDomino.x = 125;     rectDomino.y = 577; rectDomino.w = 50; rectDomino.h = 90;
            }
            nb=0;
            pointeurListe = joueurs[tour].liste;
            while(pointeurListe != NULL)
            {
                if(SDL_PointInRect(&p, &rectDomino))
                {
                    indiceDomino = nb;
                    domino_a_jouer = retourne_noeud(&joueurs[tour].liste, nb);
                    break;
                }
                else
                    nb++;
                pointeurListe = pointeurListe->suivant;
                if(tour==0 || tour==2)
                    rectDomino.y += 53;
                else if(tour==1 || tour==3)
                    rectDomino.x += 53;
            }
            if(SDL_PointInRect(&p, &positionDirection))
                direction = (p.x >= 270);
            if(direction == 1 || direction == 0)
            {
                position = *plateau;
                while (position->suivant != NULL)
                    position = position->suivant;
                if(( (domino_a_jouer->valeurDroite == position->valeurDroite || domino_a_jouer->valeurGauche == position->valeurDroite) && direction) || ((domino_a_jouer->valeurDroite == (*plateau)->valeurGauche || domino_a_jouer->valeurGauche == (*plateau)->valeurGauche) && !direction))
                {
                    termine = 1;
                    *plateau = ajout_plateau(plateau, supprime_noeud(&joueurs[tour].liste, indiceDomino), direction);
                    interface_plateau(window, renderer, texture, param, joueurs, plateau, tour);
                }
            }
            direction = -1;
            if(SDL_PointInRect(&p, &positionPioche) && !estPioche)
            {
                if(*pioche != NULL)
                {
                    Domino *noeud = piocher(pioche), *tmp = joueurs[tour].liste;
                    tmp->precedent = noeud;
                    noeud->suivant = tmp;
                    joueurs[tour].liste = noeud;
                }
                interface_plateau(window, renderer, texture, param, joueurs, plateau, tour);
                estPioche = 1;
            }
            if(SDL_PointInRect(&p, &positionPasse) && estPioche)
                termine = 1;
        }
        if(termine)
            return;
        if(quit)
            {detruie(window, renderer, texture);break;}
    }
}