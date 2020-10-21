#include "jeu.h"
#include "socket.h"
void game()
{
    unsigned short x = self.x, y = self.y;
    int ch;
    while(x != 0 && x != TAILLE_1 - 1 &&
        y != 0 && y != TAILLE_1 - 1){
            if(x-1 >= 0){
                if(labyrinthe[x-1][y] == 0 || labyrinthe[x-1][y] == 4) labyrinthe[x-1][y] = 4;
                else if(labyrinthe[x-1][y] == 6) labyrinthe[x-1][y] = 5;
                else labyrinthe[x-1][y] = 3;
            }
            if(x+1 < TAILLE_1){
                if(labyrinthe[x+1][y] == 0 || labyrinthe[x+1][y] == 4) labyrinthe[x+1][y] = 4;
                else if(labyrinthe[x+1][y] == 6) labyrinthe[x-1][y] = 5;
                else labyrinthe[x+1][y] = 3;
            }
            if(y-1 >= 0){
                if(labyrinthe[x][y-1] == 0 || labyrinthe[x][y-1] == 4) labyrinthe[x][y-1] = 4;
                else if(labyrinthe[x][y-1] == 6) labyrinthe[x-1][y] = 5;
                else labyrinthe[x][y-1] = 3;
            }
            if(y+1 < TAILLE_1){
                if(labyrinthe[x][y+1] == 0 || labyrinthe[x][y+1] == 4) labyrinthe[x][y+1] = 4;
                else if(labyrinthe[x][y+1] == 6) labyrinthe[x-1][y] = 5;
                else labyrinthe[x][y+1] = 3;
            }
            print_lab();
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
            self.x = x;
            self.y = y;
            labyrinthe[x][y] = 2;
            char message[3];
            message[0] = NEW_POS;
            message[1] = x;
            message[2] = y;
            sendMessage(message, 3);
    }
}