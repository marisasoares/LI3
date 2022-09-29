#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libs/main.h"

int main(int argc, char* argv[]){
    if(strcmp(argv[1], "exercicio-1") == 0){
        parseUsers();
        parseCommits();
        parseRepos();
    }
    else if(strcmp(argv[1], "exercicio-2") == 0){
        LISTAREPOS lr = initListaRepos();
        LISTAUSERS lu = initListaUsers();
        adicionarUsers(lu);
        adicionarRepos(lu, lr);
        adicionarCommits(lu, lr);
    }

    return 0;
}
