#include "info.h"
#ifdef MINGW32
#include<winsock2.h>
#include <windows.h>
#else
// Libraries for Linux
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#endif 
#define PORT 8999

#define INIT_LABYRINTHE 'I'
#define PSEUDO 'P'
#define NEW_POS 'N'
#define WIN 'W'
SOCKET sock_client;
int init_connection();
void* read_message();
void sendMessage(const char *ecrit, int nbOctet);