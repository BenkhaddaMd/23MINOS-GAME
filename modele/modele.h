///////// MODELE /////////

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

void melange_dominos(Domino **pioche)
{
    Domino dominos[28];
    init_dominos(dominos);

    int i, alea, pris[28];
    Domino *melangeDominos = NULL, *pointeurPosition;
    for(i=0; i<28; i++)
        pris[i] = 0;

    i=0;
    alea = alea_int(28); 
    while(i<28)
    {
        alea = alea_int(28);  
        if(!pris[alea])
        {
            Domino *noeud = malloc(sizeof(Domino));
            noeud->valeurDroite = dominos[alea].valeurDroite;
            noeud->valeurGauche = dominos[alea].valeurGauche;
            noeud->suivant = NULL;
            noeud->precedent = NULL;
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
            pris[alea]=1;
            i++;      
        }
    }
    *pioche = melangeDominos;
}

Domino* piocher(Domino **dominos)
{
    Domino *noeud = *dominos;
    *dominos = (*dominos)->suivant;
    noeud->suivant = NULL;
    return noeud;
}

void distribuer_dominos(JoueurPlateau *joueurs, int nbJoueurs, Domino **pioche)
{
    int nbDist = 7;
    if(nbJoueurs > 2)
        nbDist = 5;

    for(int i = 0; i < nbJoueurs; i++)
    {
        Domino *listePosition = NULL;
        for(int j = 0; j < nbDist; j++)
        {
            if(listePosition == NULL)
            {
                joueurs[i].liste = piocher(pioche);
                listePosition = joueurs[i].liste;
            }
            else
            {
                listePosition->suivant = piocher(pioche);
                listePosition->suivant->precedent = listePosition;
                listePosition = listePosition->suivant;
            }
        }
    }
}

Domino* retourne_noeud(Domino **liste, int indice)
{
    while (indice > 0)
    {
        liste = &(*liste)->suivant;
        indice--;
    }
    return *liste;
}

Domino* supprime_noeud(Domino **liste, int indice)
{
    Domino *aRetourne;
    while (indice > 0)
    {
        liste = &(*liste)->suivant;
        indice--;
    }
    aRetourne = *liste;
    if((*liste)->precedent == NULL && (*liste)->suivant == NULL)
        *liste = NULL;
    else if((*liste)->precedent == NULL)
    {
        *liste = (*liste)->suivant;
        (*liste)->precedent = NULL;
    }
    else if((*liste)->suivant == NULL)
    {
        (*liste)->precedent->suivant = NULL;
    }
    else
    {
        (*liste)->precedent->suivant = aRetourne->suivant;
        (*liste)->precedent = aRetourne->precedent;
    } 
    aRetourne->precedent = NULL;
    aRetourne->suivant = NULL;
    return aRetourne; 
}

Domino* qui_commence(JoueurPlateau *joueur,int nb, int *tour)
{
    int nbDist = 7;
    Domino *position;
    int max=0,  positionPar = 0, positionMax;
    if(nb > 2)
        nbDist = 5;

    for(int k=0; k<nb; k++)
    {
        position = joueur[k].liste;
        while(position != NULL)
        {
            if((position->valeurDroite) == (position->valeurGauche) && max <= (position->valeurDroite))
            {
                max = position->valeurDroite;
                positionMax = positionPar;
            }
            position = position->suivant;
            positionPar = positionPar+1;
        }
    }
     *tour = ((positionMax/nbDist) + 1) % nb;
     return supprime_noeud(&joueur[positionMax/nbDist].liste,positionMax%nbDist);
}
void permute(Domino *domino)
{
    domino->valeurDroite += domino->valeurGauche;
    domino->valeurGauche = domino->valeurDroite - domino->valeurGauche;
    domino->valeurDroite -= domino->valeurGauche; 
}

Domino* ajout_plateau(Domino **plateau, Domino *domino_a_jouer, int emplacement)
{
    Domino **position = plateau;  
    if(!emplacement)
    {
        if(domino_a_jouer->valeurDroite == (*plateau)->valeurGauche || domino_a_jouer->valeurGauche == (*plateau)->valeurGauche)
        {
            if(domino_a_jouer->valeurDroite != (*plateau)->valeurGauche)
                permute(domino_a_jouer);
            (*plateau)->precedent = domino_a_jouer;
            domino_a_jouer->suivant = *plateau;
            return domino_a_jouer;
        }
    }
    else
    {
        while ((*position)->suivant != NULL)
            position = &(*position)->suivant;
        if(domino_a_jouer->valeurDroite == (*position)->valeurDroite || domino_a_jouer->valeurGauche == (*position)->valeurDroite)
        {
            if(domino_a_jouer->valeurGauche != (*position)->valeurDroite)
                permute(domino_a_jouer);
            (*position)->suivant = domino_a_jouer;
            domino_a_jouer->precedent = *position;
            return *plateau;
        }
    }
    
}

void actualise_plateau(Domino **plateau)
{
    Domino **position = plateau;
    while (((*position)->suivant)->suivant != NULL)
            position = &(*position)->suivant;
    (*position)->valeurDroite = 7;
    (*position)->valeurGauche = 7;
    (*position)->precedent = *plateau;
    (*plateau)->suivant = *position;
}

int est_gangne(JoueurPlateau *listJoueurs , ParametresJeu param)
{
    for(int i=0; i<param.nbJoueurs; i++)
    {
        if(listJoueurs[i].liste == NULL)
            return i; 
    }
    return -1;
}