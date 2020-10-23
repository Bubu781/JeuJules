#include "jeu.h"
int main(int argc, char const *argv[])
{
    init_connection();
    selfPlayer = malloc(sizeof(struct myPlayer));
    selfPlayer->x = -1;
    selfPlayer->y = -1;
    other1 = malloc(sizeof(struct myPlayer));
    other1->x = -1;
    other1->y = -1;
    HANDLE thread = CreateThread(NULL, 0, read_message, NULL, 0, NULL);
    game();
    return 0;
}