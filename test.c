#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int len(char *string) {
    if (*string == '\0') {
        return 0; //the \0 char not count for the string length in our world
    }

    return 1 + len(string + 1);
}

char getcategory(int *age){
    if (*age<16){
        return 'J';
    }else if(*age>60){
        return 'S';
    }else {
        return 'M';
    }
}

int main(int argc, char *argv[]){
    int age = atoi(argv[1]);
    char *message = malloc(1+1+len(argv[1]));
    printf("%d\n", age);
    printf("%c\n", getcategory(&age));
    message[0] = getcategory(&age);
    
    printf("%s\n", message);
    free(message);
    return 0;
}