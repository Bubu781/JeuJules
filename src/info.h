#include <stdlib.h>
#include <sys/types.h>
#ifdef MINGW32
#include<winsock2.h>
#include <windows.h>
#include <conio.h>
#endif 
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#define TAILLE_1 9
#define CENTER 5
struct myPlayer{
    int x;
    int y;
    char pseudo;
};
struct myPlayer* selfPlayer;
struct myPlayer* other1;
unsigned short labyrinthe[TAILLE_1][TAILLE_1];