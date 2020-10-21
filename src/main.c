#include "lab.h"
#include "jeu.h"

int main(int argc, char const *argv[])
{
    unsigned short labyrinthe[TAILLE_1][TAILLE_1];
    srand(time(NULL));

    create_lab(labyrinthe);
    game(labyrinthe);
    return 0;
}