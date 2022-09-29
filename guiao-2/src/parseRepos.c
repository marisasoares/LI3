#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libs/parseRepos.h"


#define BUFF_SIZE 100000

int adicionarR(char *line, LISTAREPOS lr, LISTAUSERS u){
    char *fields = strdup(line);
    char *temp, *resto, *lang, *date, *desc = malloc(sizeof(char)*200); 
    int id, owner_id, r=1;
    for(int i=0; (temp=(strsep(&fields, ";"))) != NULL && i<9; i++){
        switch (i){
            case 0:
                id = strtol(temp,&resto,10);
                break;
            case 1: 
                owner_id = strtol(temp,&resto,10);
                break;
            case 5:
                desc = strdup(temp);
                break;
            case 6:
                lang = strdup(temp);
                break;
            case 8:
                date = strdup(temp);
                break;
            }
    }
    REPOS repos = initRepos(id, owner_id, lang, date, desc);
    if(g_hash_table_lookup(lr->repos, id) == NULL && g_hash_table_lookup(u->user, owner_id)){
        addRepos(lr,repos);
    }else r=0;

    return r;

}

void adicionarRepos(LISTAUSERS u, LISTAREPOS l){
    FILE *f = fopen ("entrada/repos-g2.csv", "r+");
    char* file = malloc(sizeof(char)*BUFF_SIZE);

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char *line = strdup((strsep(&temp, "\n")));
        adicionarR(line, l, u);
        
    }

}
