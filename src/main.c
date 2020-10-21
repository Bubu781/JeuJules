#include "lab.h"
#include "jeu.h"
#include "socket.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    sock_client = init_connection();
    pthread_t thread;
    pthread_create(&thread,NULL, read_message, NULL);
    game();
    return 0;
}