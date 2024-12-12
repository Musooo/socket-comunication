#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include "func.h"

#define IPADDRESS "127.0.0.1"
#define PORT 1313


int main(int argc, char **argv) {
    if (argc != 2)
        return -1;
    
    char buffer[100]; 
    char *message = malloc(len(argv[1])+2); 
    strcpy(message, "0"); //init message
    strcat(message, argv[1]);

    int sockfd, n; 
    struct sockaddr_in servaddr; 
      
    // clear servaddr 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 
      
    // create datagram socket 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
      
    // connect to server 
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
        printf("\n Error : Connect Failed \n"); 
        exit(0); 
    } 
  
    // request to send datagram 
    // no need to specify server address in sendto 
    // connect stores the peers IP and port 
    sendto(sockfd, message, 1000, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
    free(message);


    while (1){
        // waiting for response 
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
        puts(buffer);
    }
 

    // close the descriptor 
    close(sockfd); 
} 