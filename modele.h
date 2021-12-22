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

void melange_dominos(Domino *dominos, Domino **pioche)
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
    *pioche = melangeDominos;
}

Domino* piocher(Domino **dominos)
{
    Domino *noeud = *dominos;
    *dominos = (*dominos)->suivant;
    noeud->suivant = NULL;
    return noeud;
}

void distribuer_dominos(JoueurPlateau *joueur, int nbJoueurs, Domino **pioche, int nbDist)
{
    for(int i = 0; i < nbJoueurs; i++)
    {
        Domino *listePosition = NULL;
        for(int j = 0; j < nbDist; j++)
        {
            if(listePosition == NULL)
            {
                joueur[i].liste = piocher(pioche);
                listePosition = joueur[i].liste;
                listePosition->precedent = NULL;
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

Domino* supprime_noeud(Domino **liste, int indice)
{
    Domino *aRetourne;
    while (indice > 0)
    {
        liste = &(*liste)->suivant;
        indice--;
    }
    aRetourne = *liste;
    if((*liste)->precedent == NULL)
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

void qui_commence(JoueurPlateau *joueur,int nb, int nbDist)
{
    Domino *position;
    int max=0,  positionPar = 0, positionMax;
    for( int k=0; k<nb; k++)
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
     printf(" le domaino a commence [ %d | %d ]\n", max,max);
     printf(" joueur %d indice %d \n", positionMax/nbDist, positionMax%nbDist);
     position = supprime_noeud(&joueur[positionMax/nbDist].liste,positionMax%nbDist);
}