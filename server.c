#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 20002

#ifndef SO_REUSEPORT
#define SO_REUSEPORT 15
#endif

int totj = 0;
int totm = 0;
int tots = 0;

typedef struct{
    char category;
    int number;
}identifier;


int len(char *string) {
    if (*string == '\0') {
        return 0; //the \0 char not count for the string length in our world
    }

    return 1 + len(string + 1);
}

identifier getcategory(int *age){
    identifier person ;
    if (*age<16){
        totj++;
        person.category = 'J';
        person.number = totj;
        return person;
        //return 'J';
    }else if(*age>60){
        tots++;
        person.category = 'S';
        person.number = tots;
        return person;
        //return 'S';
    }else {
        totm++;
        person.category = 'M';
        person.number = totm;
        return person;
        //return 'M';
    }
}

int pow(int n,int b){
    if (b==0){
        return 1;
    }
    return n*pow(n,b-1);
}

int stringtoint(char *arr,int pos,int index){
    if (pos==0){
        return 0;
    }

    return (arr[index]-48)*pow(10,pos-1)+stringtoint(arr,pos-1,index+1);
}

void messageprocess(char *name, char *age, const char *msg) {
    int mod = 0;

    while (*msg != '\0') {
        if (*msg == '-') {
            mod++;
        } else if (!mod) {
            *name = *msg;
            name++;
        } else {
            *age = *msg;
            age++;
        }
        msg++;
    }
    *name = '\0';
    *age = '\0';
}

int main(int argc, char *argv[]){
        int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // attaching socket to the port 20002
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // attaching socket to the port 20002
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    while(1){
        if (listen(server_fd, 10) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read(new_socket, buffer, 1024 - 1); // subtract 1 for the '\0'
        buffer[valread] = '\0'; // Ensure null-terminated string
        printf("%s\n", buffer);
        //TODO break the while
        
        char *name = malloc(valread + 1);
        char *agestring = malloc(valread + 1);
        if (name == NULL || agestring == NULL) {
            perror("Failed to allocate memory");
            close(new_socket);
            continue;
        }

        messageprocess(name,agestring,buffer);
        int age = stringtoint(agestring, len(agestring), 0);
        //char category = getcategory(&age);
        identifier person = getcategory(&age);
        char *message = malloc(100);
        char number[50];
        sprintf(number, "%d", person.number);
        strcpy(message, &person.category);
        strcat(message, number);
 
        send(new_socket, message, len(message), 0);
        printf("identifier sent\n");

        free(name);
        free(agestring);
        free(message);

        // closing the connected socket
        close(new_socket);
    }

    // closing the listening socket
    close(server_fd);
    return 0;
}