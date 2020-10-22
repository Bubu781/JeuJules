#include "info.h"
void gotoligcol( int lig, int col ){
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
void print_lab()
{
    gotoligcol(0,0);
    printf("                      \n");
    for(unsigned short i = 0; i < TAILLE_1; i++){
        printf(" ");
        for(unsigned short j = 0; j < TAILLE_1; j++)
            printf(" ");
        printf(" \n");
    }
    printf("                      \n");

    gotoligcol(0,0);
    printf("______________________\n");
    for(unsigned short i = 0; i < TAILLE_1; i++){
        printf("|");
        for(unsigned short j = 0; j < TAILLE_1; j++)
            if(/*labyrinthe[i][j] == 1 || */labyrinthe[i][j] == 3)printf("%c", 219);
            else if(/*labyrinthe[i][j] == 0 || labyrinthe[i][j] == 4*/ labyrinthe[i][j] != 2 && labyrinthe[i][j] != 5) printf(" ");
            else if(labyrinthe[i][j] == 2) printf("A");
            else if(labyrinthe[i][j] == 5) printf("B");
        printf("|\n");
    }
    printf("______________________\n");
}