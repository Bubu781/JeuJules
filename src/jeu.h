#include "lab.h"
#define PORT 3000

#define INIT_LABYRINTHE 'I'
#define PSEUDO 'P'
#define NEW_POS 'N'
#define WIN 'W'
SOCKET sock_client;
int init_connection();
DWORD WINAPI read_message();
void sendMessage(const char *ecrit, int nbOctet);

void game();