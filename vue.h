
// VUE 

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