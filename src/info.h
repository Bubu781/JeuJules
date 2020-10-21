#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#ifdef MINGW32
#include <conio.h>
#endif
#define TAILLE_1 20
#define CENTER 10
typedef struct player{
    int x;
    int y;
    char pseudo;
}t_player;
t_player self, other1;
unsigned short labyrinthe[TAILLE_1][TAILLE_1];