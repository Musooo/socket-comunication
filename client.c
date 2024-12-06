#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 20002
#define MESSAGE_SEPARATOR "-"

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

    char *message = malloc(len(argv[1])+len(argv[2])+1+1); //+1 for '\0' char and for '-'
    strcpy(message, argv[1]);
    strcat(message, MESSAGE_SEPARATOR);
    strcat(message, argv[2]);

    char buffer[1024] = { 0 };

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(client_fd, message, len(argv[1])+len(argv[2])+1, 0);
    printf("Information sent to the server\n");
    valread = read(client_fd, buffer,
                   1024 - 1);
    printf("%s\n", buffer);

    close(client_fd);
    free(message);
    return 0;
}