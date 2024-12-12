#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "func.h"
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>


#define PORT 1313

typedef struct {
    struct sockaddr_in client;
    char *name;
}user;


user *userarr = NULL;
int size = 0;

void alloclient(struct sockaddr_in client, char *name){
    userarr = (user* ) realloc(userarr, (size + 1) * sizeof(user));
    userarr[size].client = client;
    userarr[size].name = strdup(name);
    size++;
}

void dealloc(){
    for (int i = 0; i < size; i++) {
        free(userarr[i].name);
    }
    free(userarr);
}

int count = 0;

void *countt(void *ptr){
    count++;
}

int main() {
    pthread_t thread_id;
    char buffer[100]; 
    char *message = "Hello Client"; 
    int listenfd, len; 
    struct sockaddr_in servaddr, cliaddr; 
    bzero(&servaddr, sizeof(servaddr)); 

    // Create a UDP Socket 
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);         
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET;
    // bind server address to socket descriptor 
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
    pthread_create(&thread_id, NULL, countt, NULL);
    while (1){
        //receive the datagram 
        len = sizeof(cliaddr); 
        int n = recvfrom(listenfd, buffer, sizeof(buffer), 
            0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
        
        buffer[n] = '\0'; 
        puts(buffer); 
        if (buffer[0]=='0'){
            memmove(buffer, buffer + 1, strlen(buffer));
            alloclient(cliaddr,buffer);
        }
        
        // send the response 
        sendto(listenfd, message, 1000, 0, 
            (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    }

    dealloc();
    return 0;
}