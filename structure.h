///////// STRUCTURE /////////

typedef struct domino{
    int valeurGauche;
    int valeurDroite;
    struct domino* suivant;

}Domino;



typedef struct joueur{
    char nom[25];
    int scoreDominos;
    int scoreTriominos;
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
    Joueur infos;
    Domino* liste;
}JoueurPlateau;