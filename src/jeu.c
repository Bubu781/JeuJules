#include "info.h"
void game(unsigned short labyrinthe[TAILLE_1][TAILLE_1])
{
    unsigned short x = CENTER, y = CENTER;
    int ch;
    while(x != 0 && x != TAILLE_1 - 1 &&
        y != 0 && y != TAILLE_1 - 1){
            if(x-1 >= 0){
                if(labyrinthe[x-1][y] == 0 || labyrinthe[x-1][y] == 4) labyrinthe[x-1][y] = 4;
                else labyrinthe[x-1][y] = 3;
            }
            if(x+1 < TAILLE_1){
                if(labyrinthe[x+1][y] == 0 || labyrinthe[x+1][y] == 4) labyrinthe[x+1][y] = 4;
                else labyrinthe[x+1][y] = 3;
            }
            if(y-1 >= 0){
                if(labyrinthe[x][y-1] == 0 || labyrinthe[x][y-1] == 4) labyrinthe[x][y-1] = 4;
                else labyrinthe[x][y-1] = 3;
            }
            if(y+1 < TAILLE_1){
                if(labyrinthe[x][y+1] == 0 || labyrinthe[x][y+1] == 4) labyrinthe[x][y+1] = 4;
                else labyrinthe[x][y+1] = 3;
            }
            print_lab(labyrinthe);
#ifdef MINGW32
            ch = getch();
#else
            ch = getchar();
#endif
            labyrinthe[x][y] = 0;
            if(ch == 'z' && labyrinthe[x-1][y] == 4) x--;
            else if(ch == 's' && labyrinthe[x+1][y] == 4) x++;
            else if(ch == 'q' && labyrinthe[x][y-1] == 4) y--;
            else if(ch == 'd' && labyrinthe[x][y+1] == 4) y++;
            labyrinthe[x][y] = 2;
    }
}