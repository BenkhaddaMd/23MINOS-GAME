///////// STRUCTURE /////////

typedef struct domino{
    int valeurGauche;
    int valeurDroite;
    struct domino* suivant;
    struct domino* precedent;
}Domino;

typedef struct joueur{
    char *nom;
    int score;
}Joueur;

struct triomino{
    int valeurGauche;
    int valeurDroite;
    int valeurCentre;
    struct domino* gauche;
    struct domino* droite;
    struct domino* centre;
}Triomino;

typedef struct joueurPlateau{
    Joueur* infos;
    Domino* liste;
}JoueurPlateau;

typedef struct parametresJeu{
    int estDomino;
    int estTriomino;
    int nbJoueurs;
}ParametresJeu;