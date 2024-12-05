#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 20001

int len(char *string) {
    if (*string == '\0') {
        return 0; //the \0 char not count for the string length in our world
    }

    return 1 + len(string + 1);
}

int main(int argc, char *argv[]){ // [1] name [2] age
    if (argc < 3) {
        printf("Usage: %s <name> <age>\n", argv[0]);
        return 1;
    }
    
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;

    char* message = malloc(len(argv[1])+len(argv[2])+1);

    free(message);
    return 0;
}