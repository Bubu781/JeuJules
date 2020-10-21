#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAILLE_1 20
#define CENTER 10
void create_lab(unsigned short labyrinthe[TAILLE_1][TAILLE_1]);
unsigned short check_around(unsigned short labyrinthe[TAILLE_1][TAILLE_1], unsigned short x, unsigned short y);
void print_tab(unsigned short labyrinthe[TAILLE_1][TAILLE_1]);

void game(unsigned short labyrinthe[TAILLE_1][TAILLE_1]);
int main(int argc, char const *argv[])
{
    unsigned short labyrinthe[TAILLE_1][TAILLE_1];
    srand(time(NULL));

    create_lab(labyrinthe);
    game(labyrinthe);
    return 0;
}

void create_lab(unsigned short labyrinthe[TAILLE_1][TAILLE_1])
{
    unsigned short x = CENTER, y = CENTER;
    short cas = -1, holes = 0;
    unsigned int turn = 0;
    for(unsigned short i = 0; i < TAILLE_1; i++){
        for(unsigned short j = 0; j < TAILLE_1; j++)
            labyrinthe[i][j] = 1;
    }
    while(x != 0 && x != TAILLE_1 - 1 &&
        y != 0 && y != TAILLE_1 - 1){
        if(rand() % 2){ //modifier x
            if(rand() % 2){
                if(labyrinthe[x-1][y] != 0 && check_around(labyrinthe, x-1, y) && (cas != 0 || turn % 3 == 0)){
                    x--;
                    cas = 0;
                }
            }else if(labyrinthe[x+1][y] != 0 && check_around(labyrinthe, x+1, y) && (cas != 1 || turn % 3 == 0)){
                x++;
                cas = 1;
            }
        }else{ //modifier y
            if(rand() % 2){
                if(labyrinthe[x][y-1] != 0 && check_around(labyrinthe, x, y-1) && (cas != 2 || turn % 3 == 0)){
                    y--;
                    cas = 2;
                }
            }else if(labyrinthe[x][y+1] != 0 && check_around(labyrinthe, x, y+1) && (cas != 3 || turn % 3 == 0)){
                y++;
                cas = 3;
            }
        }
        turn++;
        labyrinthe[x][y] = 0;
        if(turn > TAILLE_1 * TAILLE_1){
            create_lab(labyrinthe);
            return;
        }
    }
    while(holes < TAILLE_1*TAILLE_1/3){
        x = rand()%TAILLE_1;
        y = rand()%TAILLE_1;
        if(labyrinthe[x][y] == 1 && check_around(labyrinthe, x, y)==1 && x != 0 && x != TAILLE_1 - 1 && y != 0 && y != TAILLE_1 - 1){
            labyrinthe[x][y] = 0;
            holes++;
        }
    }
    for(unsigned short i = CENTER - 2; i < CENTER + 2; i++)
        for(unsigned short j = CENTER - 2; j < CENTER + 2; j++)
            labyrinthe[i][j] = 0;
    labyrinthe[CENTER][CENTER] = 2;
}

unsigned short check_around(unsigned short labyrinthe[TAILLE_1][TAILLE_1], unsigned short x, unsigned short y){
    unsigned short sum = 0;
    sum = labyrinthe[x-1][y] + labyrinthe[x+1][y] + labyrinthe[x][y-1] + labyrinthe[x][y+1];
    if(sum != 3) return 0;
    else return 1;
}


void print_tab(unsigned short labyrinthe[TAILLE_1][TAILLE_1])
{
    system("clear");
    printf("______________________\n");
    for(unsigned short i = 0; i < TAILLE_1; i++){
        printf("|");
        for(unsigned short j = 0; j < TAILLE_1; j++)
            if(/*labyrinthe[i][j] == 1 || */labyrinthe[i][j] == 3)printf("%c", 219);
            else if(/*labyrinthe[i][j] == 0 || labyrinthe[i][j] == 4*/ labyrinthe[i][j] != 2) printf(" ");
            else printf("A");
        printf("|\n");
    }
    printf("______________________\n");
}

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
            print_tab(labyrinthe);
            ch = getchar();
            labyrinthe[x][y] = 0;
            if(ch == 'z' && labyrinthe[x-1][y] == 4) x--;
            else if(ch == 's' && labyrinthe[x+1][y] == 4) x++;
            else if(ch == 'q' && labyrinthe[x][y-1] == 4) y--;
            else if(ch == 'd' && labyrinthe[x][y+1] == 4) y++;
            labyrinthe[x][y] = 2;
    }
}