#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <glib.h>
#include "../libs/parseCommits.h"

#define BUFF_SIZE 10000


int adicionarC(char *line, LISTAREPOS lr, LISTAUSERS u, LISTACOMMITS lc, int i){
    char *fields = strdup(line);
    char *temp, *resto, *date = malloc(sizeof(char)*20), *message = malloc(sizeof(char)*500); 
    int repo_id, author_id, commiter_id, r=1;


    for(int i=0; (temp=(strsep(&fields, ";"))) != NULL && i<5; i++){
        switch (i){
            case 0:
                repo_id = strtol(temp,&resto,10);
                break;
            case 1: 
                author_id = strtol(temp,&resto,10);
                break;
            case 2:
                commiter_id = strtol(temp,&resto,10);
                break;
            case 3:
                date = strdup(temp);
                break;
            case 4:
                message = strdup(temp);
                break;
            }
    }
    COMMIT c = initCommit(repo_id, author_id, commiter_id, date, message);
    if(g_hash_table_lookup(lr->repos, repo_id) && g_hash_table_lookup(u->user, author_id) && g_hash_table_lookup(u->user, commiter_id)){
        addCommit(lc, c, i);
    }else r=0;

    return r;

}

void adicionarCommits(LISTAUSERS u, LISTAREPOS r, LISTACOMMITS c){
    FILE *f = fopen ("entrada/commits-g2.csv", "r+");
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    int i=0;

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char *line = strdup(strsep(&temp, "\n"));
        adicionarC(line, r, u, c, i);   
        i++;
    }

   
}
