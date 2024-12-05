#include <stdio.h>
#include <string.h>



int len(char *string) {
    if (*string == '\0') {
        return 0; //the \0 char not count for the string length in our world
    }

    return 1 + len(string + 1);
}

int main(int argc, char *argv[]){
    int length = len(argv[1]);

    printf("%d\n", length);
    return 0;
}