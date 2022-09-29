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
    char *temp, *resto, *date , *message;
    int m;
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
                m = strlen(message);
                break;
            }
    }
    COMMIT c = initCommit(repo_id, author_id, commiter_id, date, m);

    if(g_hash_table_lookup(get_catalogoRepos(lr), repo_id) && g_hash_table_lookup(get_catalogoUsers(u), author_id) && g_hash_table_lookup(get_catalogoUsers(u), commiter_id)){
        addCommit(lc, c, i);
    }else r=0;

    //free(date);
    //free(message);
    return r;

}

int linhaValidaCommits(char *line){
    char *fields = strdup(line);
    char *temp; 
    int i=0, r=1;
    for(i=0; (temp=(strsep(&fields, ";"))) != NULL && i<4; i++){
         if(strcmp(temp,"") == 0){ i=4; r=0;}
        switch (i){
            case 0:
                r = isInt(temp); 
                if (r==0) i=4;
                break;
            case 1: 
                r = isInt(temp); 
                if (r==0) i=4;
                break;
            case 2:
                r = isInt(temp); 
                if (r==0) i=4;
                break;
            case 3:
                r = verificarData(temp);
                break;
        }
    }
    
    return r;
}

void adicionarCommits(LISTAUSERS u, LISTAREPOS r, LISTACOMMITS c){
    FILE *f = fopen ("entrada/commits-g3.csv", "r+");
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    int i=0;

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char *line = strdup(strsep(&temp, "\n"));
        if(linhaValidaCommits(line)) adicionarC(line, r, u, c, i);   
        i++;
    }
    //free(file);
   
}
