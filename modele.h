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

void distribuer_dominos(JoueurPlateau *joueur, int nb, Domino **pioche)
{
    for(int i = 0; i < nb; i++)
    {
        Domino *listePosition = NULL;
        for(int j = 0; j < 7; j++)
        {
            if(listePosition == NULL)
            {
                joueur[i].liste = piocher(pioche);
                listePosition = joueur[i].liste;
            }
            else
            {
                listePosition->suivant = piocher(pioche);
                listePosition = listePosition->suivant;
            }
        }
    }
}