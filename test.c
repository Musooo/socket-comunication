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

    int num = 100;

    printf("%c\n", num);

    return 0;
}