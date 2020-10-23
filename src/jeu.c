#include "jeu.h"
int ligne = 0;
int init_connection(void){

    SOCKADDR_IN server;
	
#ifdef MINGW32
	// code for windows only
		WSADATA wsa;
    printf("\nInitialising Winsock...");
    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
#endif

    //Create socket
    sock_client = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_client == INVALID_SOCKET) {
        printf("Could not create socket");
        exit (EXIT_FAILURE);
    }
    puts("Client Socket created");

    // Define the socket remote address : 192.168.0.111:8888
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);


    //Connect to remote server
    if (connect(sock_client, (SOCKADDR *) &server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        exit (EXIT_FAILURE);
    }
    puts("Connected\n");

    return sock_client;
}

DWORD WINAPI read_message()
{
    int end = 0;
    while(end == 0)
    {
        char server_reply[1000] = {0};
        int i=0;
        int j=0; 
        int k;   
        int typemsg = 0;
        char taille;
        int checksum = 0;
        if(recv(sock_client, server_reply,100,0) < 0) puts("erreur\n");
        else if(server_reply[0] != 0){
            if(server_reply[0] == INIT_LABYRINTHE){
                k = 1;
                for(int j = 0; j < TAILLE_1; j++){
                    labyrinthe[ligne][j] = '0' - server_reply[k];
                    k++;
                }
                ligne++;
            }else if(server_reply[0] == PSEUDO){
                selfPlayer->pseudo = server_reply[1];
                if(selfPlayer->pseudo == 'A')
                    other1->pseudo = 'B';
                else
                    other1->pseudo = 'A';
            }else if(server_reply[0] == NEW_POS){
                if(server_reply[1] == selfPlayer->pseudo){
                    selfPlayer->x = server_reply[2];
                    selfPlayer->y = server_reply[3];
                    labyrinthe[selfPlayer->x][selfPlayer->y]=2;
                }else if(server_reply[1] == other1->pseudo){
                    if(other1->x != 0 && other1->y !=0)
                    labyrinthe[other1->x][other1->y] = 0;
                    other1->x = server_reply[2];
                    other1->y = server_reply[3];
                    if(other1->x-selfPlayer->x>=-1 && other1->x-selfPlayer->x<=1 && other1->y-selfPlayer->y>=-1 && other1->y-selfPlayer->y<=1)
                        labyrinthe[other1->x][other1->y] = 5;
                    else
                        labyrinthe[other1->x][other1->y] = 6;
                }
#ifdef MINGW32
                system("cls");
#else
                system("clear");
#endif
                print_lab();
            }else if(server_reply[0] == WIN){
                selfPlayer->x = 0;
                selfPlayer->y = 0;
                end = 1;
            }
        }
        usleep(1);
    }
	return 0;
}

void sendMessage(const char *ecrit, int nbOctet) {

    //En cas d'erreur lors de l'envoi
    if (send (sock_client, ecrit, nbOctet, 0) < 0)
    {
        printf ("Error : When sending new message\n");

    }
}

void game()
{
    while(selfPlayer->x == -1)sleep(1);
    unsigned short x = selfPlayer->x, y = selfPlayer->y;
    int ch;
    while(x != 0 && x != TAILLE_1 - 1 &&
        y != 0 && y != TAILLE_1 - 1){
            if(labyrinthe[x-1][y] == 5) labyrinthe[x-1][y] = 6;

            if(labyrinthe[x+1][y] == 5) labyrinthe[x+1][y] = 6;

            if(labyrinthe[x][y-1] == 5) labyrinthe[x][y-1] = 6;

            if(labyrinthe[x][y+1] == 5) labyrinthe[x][y+1] = 6;
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
            selfPlayer->x = x;
            selfPlayer->y = y;
            labyrinthe[x][y] = 2;
            char message[3];
            message[0] = NEW_POS;
            message[1] = x;
            message[2] = y;
            if(x-1 >= 0){
                if(labyrinthe[x-1][y] == 0 || labyrinthe[x-1][y] == 4) labyrinthe[x-1][y] = 4;
                else if(labyrinthe[x-1][y] == 6) labyrinthe[x-1][y] = 5;
                else if(labyrinthe[x-1][y] != 5) labyrinthe[x-1][y] = 3;
            }
            if(x+1 < TAILLE_1){
                if(labyrinthe[x+1][y] == 0 || labyrinthe[x+1][y] == 4) labyrinthe[x+1][y] = 4;
                else if(labyrinthe[x+1][y] == 6) labyrinthe[x+1][y] = 5;
                else if(labyrinthe[x+1][y] != 5) labyrinthe[x+1][y] = 3;
            }
            if(y-1 >= 0){
                if(labyrinthe[x][y-1] == 0 || labyrinthe[x][y-1] == 4) labyrinthe[x][y-1] = 4;
                else if(labyrinthe[x][y-1] == 6) labyrinthe[x][y-1] = 5;
                else if(labyrinthe[x][y-1] != 5) labyrinthe[x][y-1] = 3;
            }
            if(y+1 < TAILLE_1){
                if(labyrinthe[x][y+1] == 0 || labyrinthe[x][y+1] == 4) labyrinthe[x][y+1] = 4;
                else if(labyrinthe[x][y+1] == 6) labyrinthe[x][y+1] = 5;
                else if(labyrinthe[x][y+1] != 5) labyrinthe[x][y+1] = 3;
            }
            print_lab();
            sendMessage(message, 3);
            
    }
    shutdown(sock_client, SD_SEND); //SD_BOTH will cause ECONNRESET
    shutdown(sock_client, SD_RECEIVE); //SD_BOTH will cause ECONNRESET
    closesocket(sock_client);
    WSACleanup();
}