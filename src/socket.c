#include "socket.h"
int init_connection(void){
    SOCKET sock_client;

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

void* read_message()
{
    char server_reply[1000] = {0};
    int i=0;
    int j=0;    
	int typemsg = 0;
    char taille;
	int checksum = 0;
    if(recv(sock_client, server_reply,100,0) < 0) puts("erreur\n");
    else if(server_reply[0] != 0){
        if(server_reply[0] == INIT_LABYRINTHE){
            int k = 1;
            for(int i = 0; i < TAILLE_1; i++){
                for(int j = 0; j < TAILLE_1; j++){
                    labyrinthe[i][j] = 0 - server_reply[k];
                    k++;
                }
            }
        }else if(server_reply[0] == PSEUDO){
            self.pseudo = server_reply[1];
            if(self.pseudo == 'A')
                other1.pseudo = 'B';
            else
                other1.pseudo = 'A';
        }else if(server_reply[0] == NEW_POS){
            if(server_reply[1] == self.pseudo){
                self.x = 0 - server_reply[2];
                self.y = 0 - server_reply[3];
            }else if(server_reply[1] == other1.pseudo){
                other1.x = 0 - server_reply[2];
                other1.y = 0 - server_reply[3];
                labyrinthe[other1.x][other1.y] = 6;
            }
        }else if(server_reply[0] == WIN){
            self.x = 0;
            self.y = 0;
            return NULL;
        }
    }
	return NULL;
}

void sendMessage(const char *ecrit, int nbOctet) {

    //En cas d'erreur lors de l'envoi
    if (send (sock_client, ecrit, nbOctet, 0) < 0)
    {
        printf ("Error : When sending new message\n");

    }
}