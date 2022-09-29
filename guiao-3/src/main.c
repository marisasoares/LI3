#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libs/main.h"

int main(int argc, char* argv[]){
    clock_t start=0,end=0;
    start = clock();
    SGC sgc = load_sgc();
    
    end = clock();
    printf("tempo = %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    if (argc == 2) controller(argv[1], sgc);
    if (argc == 1) controller(" ",sgc);
    else exit(0);
    
    free_sgc(sgc);
    
    return 0;
}   