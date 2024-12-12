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
struct sockaddr_in client;


int main() {    
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
        while (1){
                // bind server address to socket descriptor 
                bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

                //receive the datagram 
                len = sizeof(cliaddr); 
                int n = recvfrom(listenfd, buffer, sizeof(buffer), 
                        0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
                buffer[n] = '\0'; 
                puts(buffer); 
                        
                // send the response 
                sendto(listenfd, message, 1000, 0, 
                        (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
        }

        return 0;
} 