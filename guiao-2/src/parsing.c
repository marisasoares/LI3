#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libs/parsing.h"

void getFollowList(char* line, int list[]){
    char* sobra;
    char* temp;
    char* num;
    char *fields =strdup(line);
    
    for(int i=0; (temp=(strsep(&fields, ", []"))) != NULL ; ){ 
        num = strdup(temp); 

        if(strlen(num)){
            list[i] = strtol(num, &sobra, 10);
            i++;
        }
        
    }
}

int exists(int N, int following[], int size){
    int r=0;
    for(int i=0; i<size; i++){
        if(N == following[i]) return 1;
    }
    return r;
}
