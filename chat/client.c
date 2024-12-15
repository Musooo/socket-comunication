#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <termios.h>
#include <pthread.h>


#define IPADDRESS "127.0.0.1"
#define PORT 1313

char currentchar;
struct termios orig_termios;
char messaggio[100];

typedef struct {
    struct sockaddr_in servaddr;
    int sockfd;
}threadlistenersockets;


void configure_terminal() {
    struct termios info;
    tcgetattr(0, &orig_termios);  /* salva le impostazioni originali del terminale */
    tcgetattr(0, &info);         /* get current terminal attirbutes; 0 is the file descriptor for stdin */
    info.c_lflag &= ~ICANON;      /* disable canonical mode */
    info.c_lflag &= ~ECHO;
    info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
    info.c_cc[VTIME] = 0;         /* no timeout */
    tcsetattr(0, TCSANOW, &info); /* set immediately */
}

void resetterminal(){
    tcsetattr(0, TCSANOW, &orig_termios);
}

void *keylistener(void *ptr){
    threadlistenersockets tsockets = *(threadlistenersockets*)ptr; 

    while (1){
        currentchar = getchar();
        switch (currentchar){
        case '2':
            resetterminal();
            fgets(messaggio, sizeof(messaggio), stdin);
            messaggio[strcspn(messaggio, "\n")] = 0;

            char new_message[1024];
            snprintf(new_message, sizeof(new_message), "42%s", messaggio);

            sendto(tsockets.sockfd, new_message, strlen(new_message), 0, (struct sockaddr*)&tsockets.servaddr, sizeof(tsockets.servaddr)); 
            
            printf("you: %s\n", new_message);
            configure_terminal();
            break;
        case '3':
            exit(0);
            break;
        case '4':
            printf("no");
            break;
        default:
            break;
        }
            
    }
}

void *messageprinter(void *ptr){
    while (1){
        
    }
}

int main(int argc, char **argv) {
    if (argc != 2)
        return -1;
    printf("Benvenuto nella chat di Topolino \npremere '2' per scrivere un messaggio \n'3' per uscire \n'4' per usare lo strumentopolo");
    pthread_t keylt_id;
    char buffer[100]; 
    char *message = malloc(strlen(argv[1])+2); 
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
  
    sendto(sockfd, message, 1000, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
    free(message);

    threadlistenersockets tsockets;
    tsockets.servaddr = servaddr;
    tsockets.sockfd = sockfd;

    configure_terminal();
    pthread_create(&keylt_id, NULL, keylistener, (void *) &tsockets);
    while (1){
        // waiting for response 
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
        puts(buffer);
        memset(buffer, 0, sizeof(buffer));
    }
 

    // close the descriptor 
    close(sockfd); 
} 