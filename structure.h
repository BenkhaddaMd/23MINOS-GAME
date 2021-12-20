
typedef struct domino{
    int valeurGauche;
    int valeurDroite;
    struct domino* suivant;
}Domino;

struct triomino{
    int valeurGauche;
    int valeurDroite;
    int valeurCentre;
    struct domino* gauche;
    struct domino* droite;
    struct domino* centre;
};