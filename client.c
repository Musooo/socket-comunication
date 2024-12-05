#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 20001



int main(int argc, char *argv[]){ // [1] name [2] age
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;

    char* message = malloc(strlen(argv[1])+strlen(argv[2])+1);

    printf("name: %s\n", name);
    printf("age: %d\n", age);
    free(message);
    return 0;
}