#include <stdio.h>
#include <stdlib.h>
#define PORT 20002

int totj = 0;
int totm = 0;
int tots = 0;

char getcategory(int *age){
    if (*age<16){
        totj++;
        return 'J';
    }else if(*age>60){
        tots++;
        return 'S';
    }else {
        totm++;
        return 'M';
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

int main(int argc, char *argv[]){


    return 0;
}