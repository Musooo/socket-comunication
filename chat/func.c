

int len(char *string) {
    if (*string == '\0') {
        return 0; //the \0 char not count for the string length in our world
    }

    return 1 + len(string + 1);
}

