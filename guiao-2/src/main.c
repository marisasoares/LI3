#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libs/main.h"

int main(int argc, char* argv[]){
    clock_t start=0,end=0;
    start = clock();
    LISTAREPOS lr = initListaRepos();
    LISTAUSERS lu = initListaUsers();
    LISTACOMMITS lc = initListaCommits();


    adicionarUsers(lu);
    adicionarRepos(lu, lr);
    adicionarCommits(lu, lr, lc);
    end = clock();
    printf("tempo = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
    parseQueries(argv[1], lu, lr, lc);
    

    return 0;
}
